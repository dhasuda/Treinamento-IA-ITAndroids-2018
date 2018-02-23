//
// Created by Davi Grossi Hasuda on 22/02/2018.
//

#include "PotentialFieldPlanner.h"
#include <math.h>
#include <vector>
#include <stdio.h>

using namespace std;

PotentialFieldPlanner::~PotentialFieldPlanner() {}

PotentialFieldPlanner::PotentialFieldPlanner() {
    N_OBS = 5;
    N_WALLS = 4;
    //Dummy values for trajectory parameters.
    setTrajectoryParameters(0.1, 0.05, 100);

    //Initializes all vectors.
    obstacles_x = vector<double>(N_OBS);
    obstacles_y = vector<double>(N_OBS);
    obstacles_K1 = vector<double>(N_OBS);
    obstacles_K2 = vector<double>(N_OBS);
    obstacles_K3 = vector<double>(N_OBS);
    obstacles_R = vector<double>(N_OBS);
    walls_x1 = vector<double>(N_WALLS);
    walls_x2 = vector<double>(N_WALLS);
    walls_y1 = vector<double>(N_WALLS);
    walls_y2 = vector<double>(N_WALLS);
    walls_K1 = vector<double>(N_WALLS);
    walls_K2 = vector<double>(N_WALLS);
    walls_K3 = vector<double>(N_WALLS);
    walls_R = vector<double>(N_WALLS);

    //These variables are actually counters. They will be increased while obstacles and walls are added.
    N_OBS = 0;
    N_WALLS = 0;

    //Completely dummy values. If the algorithm runs without setting
    //these variables properly, an error message will be sent and the algorithm will stop.
    robot_x = 0;
    robot_y = 0;
    robot_vx = 0;
    robot_vy = 0;
    target_R = 0;
    target_x = 0;
    target_y = 0;
    target_vx = 0;
    target_vy = 0;
    target_K1 = 0;
    target_K2 = 0;
    target_K3 = 0;
    target_repulsive_threshold = 0;
}

PotentialFieldPlanner::PotentialFieldPlanner(int n_obs, int n_walls)
{
    N_OBS = n_obs;
    N_WALLS = n_walls;

    //Dummy values for trajectory parameters.
    setTrajectoryParameters(0.1, 0.05, 100);

    //Initializes all vectors.
    obstacles_x = vector<double>(N_OBS);
    obstacles_y = vector<double>(N_OBS);
    obstacles_K1 = vector<double>(N_OBS);
    obstacles_K2 = vector<double>(N_OBS);
    obstacles_K3 = vector<double>(N_OBS);
    obstacles_R = vector<double>(N_OBS);
    walls_x1 = vector<double>(N_WALLS);
    walls_x2 = vector<double>(N_WALLS);
    walls_y1 = vector<double>(N_WALLS);
    walls_y2 = vector<double>(N_WALLS);
    walls_K1 = vector<double>(N_WALLS);
    walls_K2 = vector<double>(N_WALLS);
    walls_K3 = vector<double>(N_WALLS);
    walls_R = vector<double>(N_WALLS);

    //These variables are actually counters. They will be increased while obstacles and walls are added.
    N_OBS = 0;
    N_WALLS = 0;

    //Completely dummy values. If the algorithm runs without setting
    //these variables properly, an error message will be sent and the algorithm will stop.
    robot_x = 0;
    robot_y = 0;
    robot_vx = 0;
    robot_vy = 0;
    target_R = 0;
    target_x = 0;
    target_y = 0;
    target_vx = 0;
    target_vy = 0;
    target_K1 = 0;
    target_K2 = 0;
    target_K3 = 0;
    target_repulsive_threshold = 0;
}

bool PotentialFieldPlanner::setRobot(double x, double y, double vx, double vy)
{
    if(vx==0 && vy==0){
        printf("Potential Fields Warning: initial direction cannot be zero.\n");
        return false;
    }
    robot_x = x;
    robot_y = y;
    robot_vx = vx;
    robot_vy = vy;
    return true;
}

bool PotentialFieldPlanner::setTarget(double x, double y, double vx, double vy, double K1, double K2, double K3, double radius, double threshold)
{
    if(vx==0 && vy==0){
        printf("Potential Fields Warning: desired direction cannot be zero.\n");
        return false;
    }
    target_R = radius;
    target_x = x;
    target_y = y;
    target_vx = vx;
    target_vy = vy;
    target_K1 = K1;
    target_K2 = K2;
    target_K3 = K3;
    target_repulsive_threshold = threshold;
    return true;
}

bool PotentialFieldPlanner::setTrajectoryParameters(double r_limit, double robot_stepsize, int max_steps)
{
    R_LIMIT = r_limit;
    THETA_LIMIT = atan(4*robot_stepsize*R_LIMIT/(4*R_LIMIT*R_LIMIT - robot_stepsize*robot_stepsize));
    MAX_STEPS = max_steps;
    this->robot_stepsize = robot_stepsize;
    return true;
}

bool PotentialFieldPlanner::addObstacle(double x, double y, double K1, double K2, double K3, double radius){
    obstacles_x[N_OBS]=(x);
    obstacles_y[N_OBS]=(y);
    obstacles_K1[N_OBS]=(K1);
    obstacles_K2[N_OBS]=(K2);
    obstacles_K3[N_OBS]=(K3);
    obstacles_R[N_OBS]=(radius);
    N_OBS++;
    return true;
}

bool PotentialFieldPlanner::addWall(double x1, double y1, double x2, double y2, double W1, double W2, double W3, double radius){
    walls_x1[N_WALLS]=(x1);
    walls_x2[N_WALLS]=(x2);
    walls_y1[N_WALLS]=(y1);
    walls_y2[N_WALLS]=(y2);
    walls_K1[N_WALLS]=(W1);
    walls_K2[N_WALLS]=(W2);
    walls_K3[N_WALLS]=(W3);
    walls_R[N_WALLS]=(radius);
    N_WALLS++;
    return true;
}

bool PotentialFieldPlanner::calculateEVector(double x, double y, double* Ex, double* Ey)
{
    (*Ex) = (*Ey) = 0.0;
    double delta_x, delta_y, distance;

    //Obstacle repulsive field.
    for(int i=0; i<N_OBS; i++){
        delta_x = x - obstacles_x[i];
        delta_y = y - obstacles_y[i];
        distance = sqrt(delta_y*delta_y + delta_x*delta_x);
        (*Ex) += obstacles_K1[i]*delta_x/(distance*(distance-obstacles_R[i]));
        (*Ex) += obstacles_K2[i]*delta_x/(distance*(distance-obstacles_R[i])*(distance-obstacles_R[i]));
        (*Ex) += obstacles_K3[i]*delta_x/(distance*(distance-obstacles_R[i])*(distance-obstacles_R[i])*(distance-obstacles_R[i]));
        (*Ey) += obstacles_K1[i]*delta_y/(distance*(distance-obstacles_R[i]));
        (*Ey) += obstacles_K2[i]*delta_y/(distance*(distance-obstacles_R[i])*(distance-obstacles_R[i]));
        (*Ey) += obstacles_K3[i]*delta_y/(distance*(distance-obstacles_R[i])*(distance-obstacles_R[i])*(distance-obstacles_R[i]));
    }

    //Wall repulsive field.
    for(int i=0; i<N_WALLS; i++){
        delta_x = ((x-walls_x1[i])*(walls_x2[i]-walls_x1[i]) + (y-walls_y1[i])*(walls_y2[i]-walls_y1[i]))*(walls_x2[i] - walls_x1[i])/
                  ((walls_x2[i]-walls_x1[i])*(walls_x2[i]-walls_x1[i]) + (walls_y2[i]-walls_y1[i])*(walls_y2[i]-walls_y1[i]));
        delta_y = ((x-walls_x1[i])*(walls_x2[i]-walls_x1[i]) + (y-walls_y1[i])*(walls_y2[i]-walls_y1[i]))*(walls_y2[i] - walls_y1[i])/
                  ((walls_x2[i]-walls_x1[i])*(walls_x2[i]-walls_x1[i]) + (walls_y2[i]-walls_y1[i])*(walls_y2[i]-walls_y1[i]));
        if(walls_x1[i]==walls_x2[i]){
            distance = delta_y/(walls_y2[i]-walls_y1[i]);
        }
        else distance = delta_x/(walls_x2[i]-walls_x1[i]);
        if (distance<0) distance=0;
        if (distance>1) distance=1;
        delta_x = x - (walls_x1[i] + distance*(walls_x2[i] - walls_x1[i]));
        delta_y = y - (walls_y1[i] + distance*(walls_y2[i] - walls_y1[i]));
        distance = sqrt(delta_y*delta_y + delta_x*delta_x);
        (*Ex) += walls_K1[i]*delta_x/(distance*(distance-walls_R[i]));
        (*Ex) += walls_K2[i]*delta_x/(distance*(distance-walls_R[i])*(distance-walls_R[i]));
        (*Ex) += walls_K3[i]*delta_x/(distance*(distance-walls_R[i])*(distance-walls_R[i])*(distance-walls_R[i]));
        (*Ey) += walls_K1[i]*delta_y/(distance*(distance-walls_R[i]));
        (*Ey) += walls_K2[i]*delta_y/(distance*(distance-walls_R[i])*(distance-walls_R[i]));
        (*Ey) += walls_K3[i]*delta_y/(distance*(distance-walls_R[i])*(distance-walls_R[i])*(distance-walls_R[i]));
    }

    //Target atractive.
    distance = sqrt(target_vx*target_vx + target_vy*target_vy);
    double target_dirx = target_vx/distance;
    double target_diry = target_vy/distance;
    double ka, kr, d=0.1;
    delta_x = x - (target_x - target_R*target_dirx);
    delta_y = y - (target_y - target_R*target_diry);
    distance = sqrt(delta_y*delta_y + delta_x*delta_x);
    if (distance > 2*target_repulsive_threshold) {
        ka = d;
        kr = 0;
    }
    else if (distance > 1.5*target_repulsive_threshold) {
        ka = (2.0*(1-d)/(target_repulsive_threshold*target_repulsive_threshold))*
             (distance-2*target_repulsive_threshold)*(distance-2*target_repulsive_threshold)
             + d;
        kr = (2.0/(target_repulsive_threshold*target_repulsive_threshold))*
             (distance-2*target_repulsive_threshold)*(distance-2*target_repulsive_threshold);
    }
    else if(distance > target_repulsive_threshold) {
        ka = (-2.0*(1-d)/(target_repulsive_threshold*target_repulsive_threshold))*
             (distance-target_repulsive_threshold)*(distance-target_repulsive_threshold)
             + 1.0;
        kr = (-2.0/(target_repulsive_threshold*target_repulsive_threshold))*
             (distance-target_repulsive_threshold)*(distance-target_repulsive_threshold)
             + 1.0;
    }
    else {
        ka = kr = 1;
    }
    (*Ex) -= ka*target_K1*delta_x/(distance*(distance-target_R));
    (*Ex) -= ka*target_K2*delta_x/(distance*(distance-target_R)*(distance-target_R));
    (*Ex) -= ka*target_K3*delta_x/(distance*(distance-target_R)*(distance-target_R)*(distance-target_R));
    (*Ey) -= ka*target_K1*delta_y/(distance*(distance-target_R));
    (*Ey) -= ka*target_K2*delta_y/(distance*(distance-target_R)*(distance-target_R));
    (*Ey) -= ka*target_K3*delta_y/(distance*(distance-target_R)*(distance-target_R)*(distance-target_R));

    //Target repulsive field.
    delta_x = x - (target_x + target_R*target_dirx);
    delta_y = y - (target_y + target_R*target_diry);
    distance = sqrt(delta_y*delta_y + delta_x*delta_x);
    (*Ex) += kr*target_K1*delta_x/(distance*(distance-target_R));
    (*Ex) += kr*target_K2*delta_x/(distance*(distance-target_R)*(distance-target_R));
    (*Ex) += kr*target_K3*delta_x/(distance*(distance-target_R)*(distance-target_R)*(distance-target_R));
    (*Ey) += kr*target_K1*delta_y/(distance*(distance-target_R));
    (*Ey) += kr*target_K2*delta_y/(distance*(distance-target_R)*(distance-target_R));
    (*Ey) += kr*target_K3*delta_y/(distance*(distance-target_R)*(distance-target_R)*(distance-target_R));

    for(int i=0; i<N_WALLS; i++){
        delta_x = ((target_x-walls_x1[i])*(walls_x2[i]-walls_x1[i]) + (target_y-walls_y1[i])*(walls_y2[i]-walls_y1[i]))*(walls_x2[i] - walls_x1[i])/
                  ((walls_x2[i]-walls_x1[i])*(walls_x2[i]-walls_x1[i]) + (walls_y2[i]-walls_y1[i])*(walls_y2[i]-walls_y1[i]));
        delta_y = ((target_x-walls_x1[i])*(walls_x2[i]-walls_x1[i]) + (target_y-walls_y1[i])*(walls_y2[i]-walls_y1[i]))*(walls_y2[i] - walls_y1[i])/
                  ((walls_x2[i]-walls_x1[i])*(walls_x2[i]-walls_x1[i]) + (walls_y2[i]-walls_y1[i])*(walls_y2[i]-walls_y1[i]));
        if(walls_x1[i]==walls_x2[i]){
            distance = delta_y/(walls_y2[i]-walls_y1[i]);
        }
        else distance = delta_x/(walls_x2[i]-walls_x1[i]);
        delta_x += walls_x1[i];
        delta_y += walls_y1[i];
        if(distance>0 && distance < 1 &&
           sqrt((delta_x-target_x)*(delta_x-target_x) + (delta_y-target_y)*(delta_y-target_y)) < 3*R_LIMIT &&
           (delta_x-target_x)*(target_dirx) + (delta_y-target_y)*(target_diry) < 0 &&
           (x-target_x)*(target_dirx) + (y-target_y)*(target_diry) > 0 &&
           sqrt((x-target_x)*(x-target_x)+(y-target_y)*(y-target_y)) < 2*target_repulsive_threshold){
            distance = sqrt((walls_x2[i]-walls_x1[i])*(walls_x2[i]-walls_x1[i]) + (walls_y2[i]-walls_y1[i])*(walls_y2[i]-walls_y1[i]));
            delta_x = (delta_x + target_x)*0.5 + (walls_x2[i] - walls_x1[i])*target_repulsive_threshold*0.7/distance - target_x;
            delta_y = (delta_y + target_y)*0.5 + (walls_y2[i] - walls_y1[i])*target_repulsive_threshold*0.7/distance - target_y;
            distance = sqrt(delta_y*delta_y + delta_x*delta_x);
            kr = 1;
            /*(*Ex) += kr*target_K1*delta_x/(distance*distance);
            (*Ex) += kr*target_K2*delta_x/(distance*distance*distance);
            (*Ex) += kr*target_K3*delta_x/(distance*distance*distance*distance);
            (*Ey) += kr*target_K1*delta_y/(distance*distance);
            (*Ey) += kr*target_K2*delta_y/(distance*distance*distance);
            (*Ey) += kr*target_K3*delta_y/(distance*distance*distance*distance);*/
        }

    }
    if(sqrt((*Ex)*(*Ex)+(*Ey)*(*Ey))<0.1){
        printf("pos: %f %f E: %f %f\n", x, y, *Ex, *Ey);
    }

    return true;
}

bool PotentialFieldPlanner::calculateTrajectory(double* sx, double* sy, double* vx, double* vy, int* n_steps)
{
    (*n_steps) = 2;
    double p1x, p1y, p2x, p2y, r, previous_nx, previous_ny;
    if(robot_vx*robot_vx + robot_vy*robot_vy==0.0){
        printf("Potential Fields Error: initial direction is zero. Simulation aborted\n");
        return false;
    }
    if(robot_vx*robot_vx + robot_vy*robot_vy==0.0){
        printf("Potential Fields Error: desired direction is zero. Simulation aborted\n");
        return false;
    }

    //(nx,ny) is current direction.
    double nx = robot_vx/sqrt(robot_vx*robot_vx + robot_vy*robot_vy);
    double ny = robot_vy/sqrt(robot_vx*robot_vx + robot_vy*robot_vy);

    //(x,y) is current position.
    double x = robot_x, y = robot_y;

    //Position 0 is initial position.
    sx[0] = robot_x;
    sy[0] = robot_y;

    //Gives a little step in the ongoing direction so it doesn't make a deep turn at start.
    x = sx[1] = sx[0] + 0.5*robot_stepsize*nx;
    y = sy[1] = sy[0] + 0.5*robot_stepsize*ny;

    //(previous_nx,previous_ny) is the previous direction. Will be used to limit turning rate.
    previous_nx = nx;
    previous_ny = ny;

    //While it doesn't reach target and doedn't exceed MAX_STEPS, calculates a new step.
    while((x-target_x)*(x-target_x) + (y-target_y)*(y-target_y) > 4*target_R*target_R && (*n_steps) < MAX_STEPS-1){

        //Calculates (nx,ny).
        calculateEVector(x, y, &nx, &ny);
        r = sqrt(nx*nx + ny*ny);
        nx /= r;
        ny /= r;

        //If the turning angle is not allowed (deep turn), calculates the allowed (nx,ny) closest
        //to desired direction.
        if (nx*previous_nx + ny*previous_ny < cos(THETA_LIMIT)){
            p1x = cos(THETA_LIMIT)*previous_nx - sin(THETA_LIMIT)*previous_ny;
            p1y = sin(THETA_LIMIT)*previous_nx + cos(THETA_LIMIT)*previous_ny;
            p2x = cos(THETA_LIMIT)*previous_nx + sin(THETA_LIMIT)*previous_ny;
            p2y = -sin(THETA_LIMIT)*previous_nx + cos(THETA_LIMIT)*previous_ny;
            if((nx-p1x)*(nx-p1x) + (ny-p1y)*(ny-p1y) > (nx-p2x)*(nx-p2x) + (ny-p2y)*(ny-p2y)){
                nx = p2x;
                ny = p2y;
            }
            else{
                nx = p1x;
                ny = p1y;
            }
        }

        //Updates current position and stores it at sx and sy vector.
        x += robot_stepsize*nx;
        y += robot_stepsize*ny;
        sx[*n_steps] = x;
        sy[*n_steps] = y;

        //Increases number of steps and updates (previous_nx,previous_ny).
        (*n_steps)++;
        previous_nx = nx;
        previous_ny = ny;
    }
    if((*n_steps) == MAX_STEPS-1){
        printf("Potential Fields Warning: number of steps limit reached.\n");
    }

    //The algorithm loop actually stops at a small distance before the target.
    //One more step is done using the desired arriving speed as E vector.
    //This makes sure that there will be always a step with a turn, even is the robot is extremely
    //close to the ball.
    r = sqrt(target_vx*target_vx + target_vy*target_vy);
    nx = target_vx/r;
    ny = target_vy/r;
    if (nx*previous_nx + ny*previous_ny < cos(THETA_LIMIT)){
        p1x = cos(THETA_LIMIT)*previous_nx - sin(THETA_LIMIT)*previous_ny;
        p1y = sin(THETA_LIMIT)*previous_nx + cos(THETA_LIMIT)*previous_ny;
        p2x = cos(THETA_LIMIT)*previous_nx + sin(THETA_LIMIT)*previous_ny;
        p2y = -sin(THETA_LIMIT)*previous_nx + cos(THETA_LIMIT)*previous_ny;
        if((nx-p1x)*(nx-p1x) + (ny-p1y)*(ny-p1y) > (nx-p2x)*(nx-p2x) + (ny-p2y)*(ny-p2y)){
            nx = p2x;
            ny = p2y;
        }
        else{
            nx = p1x;
            ny = p1y;
        }
    }
    x += robot_stepsize*nx;
    y += robot_stepsize*ny;
    sx[*n_steps] = x;
    sy[*n_steps] = y;
    previous_nx = nx;
    previous_ny = ny;

    printf("Simulation ended\n");

    //Calculates the direction of each point.
    r = sqrt(robot_vx*robot_vx + robot_vy*robot_vy);
    vx[0] = robot_vx/r;
    vy[0] = robot_vy/r;
    for(int i=1; i<(*n_steps); i++){
        r = sqrt((sx[i]-sx[i+1])*(sx[i]-sx[i+1]) + (sy[i]-sy[i+1])*(sy[i]-sy[i+1]));
        vx[i] = (sx[i+1]-sx[i])/r;
        vy[i] = (sy[i+1]-sy[i])/r;
    }

    //Sets each point i at the middle of point i+1 and point i, so
    //that each point actually have the calculated direction.
    //All archs are circles because of constant step size.
    for(int i=1; i<(*n_steps); i++){
        sx[i] = (sx[i+1]+sx[i])/2.0;
        sy[i] = (sy[i+1]+sy[i])/2.0;
    }

    return true;
}