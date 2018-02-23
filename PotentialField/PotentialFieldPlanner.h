#ifndef POTENTIALFIELD_POTENTIALFIELDPLANNER_H
#define POTENTIALFIELD_POTENTIALFIELDPLANNER_H

#include <math.h>
#include <vector>

class PotentialFieldPlanner {

public:

    PotentialFieldPlanner();

    //A constructor where you can set the number of obstacles and walls.
    //Should be the one used.
    PotentialFieldPlanner(int n_obs, int n_walls);

    virtual ~PotentialFieldPlanner();

    //Set robot initial position a velocity. Only direction is taken into account.
    bool setRobot(double x, double y, double vx, double vy);

    //Set target initial position, velocity, field constants and repulsive field threshold. Only direction is taken into account.
    bool setTarget(double x, double y, double vx, double vy, double K1, double K2, double K3, double radius, double threshold);

    //Set simulation parameters.
    bool setTrajectoryParameters(double r_limit, double robot_stepsize, int max_steps);

    //Add an obstacles with its proper constants, location and radius.
    bool addObstacle(double x, double y, double K1, double K2, double K3, double radius);

    //Add a wall with its proper constants, location and radius.
    bool addWall(double x1, double y1, double x2, double y2, double W1, double W2, double W3, double radius);

    //Given a position (x,y), calculates the desired E vector.
    bool calculateEVector(double x, double y, double* Ex, double* Ey);

    //Using all provided information, calculates the trajectory with all locations and directions
    //||(vx,vy)|| = 1.
    //Stops if MAX_STEPS is reached and returns incomplete path.
    bool calculateTrajectory(double* sx, double* sy, double* vx, double* vy, int* n_steps);

private:

    //Number of obstacles and walls
    int N_OBS, N_WALLS;

    //Information about the target location and desired arriving speed.
    //Only direction will be taken into account.
    //K1, K2 and K3 are the field constants. E = K1/r + K2/r^2 + K3/r^3,
    //where r is the distance minus the radius.
    //target_repulsive_thrshold is the minimum distance so that the target
    //repulsive filed starts acting.
    double target_x, target_y, target_K1, target_K2, target_K3;
    double target_vx, target_vy, target_R;
    double target_repulsive_threshold;

    //Information about the obstacles locations.
    //K1, K2 and K3 are the field constants. E = K1/r + K2/r^2 + K3/r^3,
    //where r is the distance minus the radius
    std::vector<double> obstacles_x, obstacles_y, obstacles_K1, obstacles_K2, obstacles_K3, obstacles_R;

    //Information about the walls locations.
    //K1, K2 and K3 are the field constants. E = K1/r + K2/r^2 + K3/r^3,
    //where r is the distance minus the radius
    std::vector<double> walls_x1, walls_y1, walls_x2, walls_y2, walls_K1, walls_K2, walls_K3, walls_R;

    //Information about the initial robot location and current speed.
    //Only direction will be taken into account, turns are limited by the parameter R_LIMIT.
    //K1, K2 and K3 are the field constants. E = K1/r + K2/r^2 + K3/r^3,
    //where r is the distance.
    double robot_x, robot_y;
    double robot_vx, robot_vy;

    //robot_stepsize is the size of each step during the simulation.
    //R_LIMIT is the minimum turing radius. THETA_LIMIT is an inside variable calculated with R_LIMIT.
    //These variables should be updated at each time the algorithm is used because os changing robot speed.
    //MAX_STEPS is the maximum number of steps. Should be calculated using the size of the positions vector provided by the user.
    double robot_stepsize;
    double R_LIMIT;
    double THETA_LIMIT;
    int MAX_STEPS;

};


#endif //POTENTIALFIELD_POTENTIALFIELDPLANNER_H
