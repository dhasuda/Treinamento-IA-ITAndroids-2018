#include <iostream>
#include "PotentialFieldPlanner.h"

int main() {

    //// Constant definition
    double K1 = 0, K2 = 0.5, K3 = 0, W1 = 0, W2 = 0.2, W3 = 0, Q1 = 0, Q2 = 200.0, Q3 = 0;
    double OBS_RADIUS = 0.075, WALL_RADIUS = 0, OBJ_RADIUS = 0.0375;
    double F_WIDTH = 1.30, F_LENGTH = 1.50;
    double space = 0.03, R_LIMIT = 0.12;
    double x0 = 0, y0 = -0.6, xf = 0, yf = 0.6, v0x = -1, v0y = 1, vfx = -1, vfy = 1;
    double h = 0.05, MAX_STEPS = 100, threshold = 2*R_LIMIT;

    //// Opening files to write
    FILE* field = fopen("field.txt", "w");
    FILE* walls = fopen("walls.txt", "w");
    FILE* obstacles = fopen("obstacles.txt", "w");
    FILE* trajectory = fopen("trajectory.txt", "w");

    PotentialFieldPlanner planner;
    planner = PotentialFieldPlanner(2, 4);
    planner.setRobot(x0, y0, v0x, v0y);
    planner.setTarget(xf, yf, vfx, vfy, Q1, Q2, Q3, OBJ_RADIUS, threshold);
    planner.setTrajectoryParameters(R_LIMIT, h, MAX_STEPS);

    planner.addObstacle(-0.30, 0.30, K1, K2, K3, OBS_RADIUS);
    fprintf(obstacles, "%f %f %f\n", -0.30, 0.30, OBS_RADIUS);
    planner.addObstacle(-0.50, 0.0, K1, K2, K3, OBS_RADIUS);
    fprintf(obstacles, "%f %f %f\n", -0.50, 0.0, OBS_RADIUS);
    planner.addObstacle(0.50, -0.30, K1, K2, K3, OBS_RADIUS);
    fprintf(obstacles, "%f %f %f\n", 0.50, -0.30, OBS_RADIUS);
    planner.addObstacle(0.10, 0.00, K1, K2, K3, OBS_RADIUS);
    fprintf(obstacles, "%f %f %f\n", 0.10, 0.00, OBS_RADIUS);

    planner.addWall(-F_LENGTH/2.0, F_WIDTH/2.0, F_LENGTH/2.0, F_WIDTH/2.0, W1, W2, W3, WALL_RADIUS);
    planner.addWall(-F_LENGTH/2.0, -F_WIDTH/2.0, F_LENGTH/2.0, -F_WIDTH/2.0, W1, W2, W3, WALL_RADIUS);
    planner.addWall(-F_LENGTH/2.0, F_WIDTH/2.0, -F_LENGTH/2.0, -F_WIDTH/2.0, W1, W2, W3, WALL_RADIUS);
    planner.addWall(F_LENGTH/2.0, F_WIDTH/2.0, F_LENGTH/2.0, -F_WIDTH/2.0, W1, W2, W3, WALL_RADIUS);
    fprintf(walls, "%f %f\n", -F_LENGTH/2.0, F_WIDTH/2.0);
    fprintf(walls, "%f %f\n", F_LENGTH/2.0, F_WIDTH/2.0);
    fprintf(walls, "%f %f\n", F_LENGTH/2.0, -F_WIDTH/2.0);
    fprintf(walls, "%f %f\n", -F_LENGTH/2.0, -F_WIDTH/2.0);
    fprintf(walls, "%f %f\n", -F_LENGTH/2.0, F_WIDTH/2.0);

    double Ex, Ey;
    for(double x = -F_LENGTH/2.0 + space; x<=F_LENGTH/2.0 - space; x+=space){
        for(double y = -F_WIDTH/2.0 + space; y<=F_WIDTH/2.0 - space; y+=space){
            planner.calculateEVector(x, y, &Ex, &Ey);
            fprintf(field, "%f %f %f %f\n", x, y, Ex, Ey);
        }

    }

    double sx[109], sy[109], vx[109], vy[109];
    int n_steps=0;
    printf("Calculating trajectory\n");
    clock_t t1 = clock();
    for(int i=0; i<1000; i++)
        planner.calculateTrajectory(sx, sy, vx, vy, &n_steps);
    printf("elapsed time is %f seconds\n", ((float)(clock()-t1))/CLOCKS_PER_SEC);
    printf("Trajectory calculated\n");
    for(int i=0; i<n_steps; i++){
        fprintf(trajectory, "%f %f %f %f\n", sx[i], sy[i], vx[i], vy[i]);
    }
    fclose(trajectory);
    fclose(field);
    fclose(walls);
    fclose(obstacles);

    return 0;
}