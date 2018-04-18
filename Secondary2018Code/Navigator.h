/*
 * trajectory.h
 *
 * Created on : 8 avril 2018
 * Author : Maxime
 */

#ifndef TRAJ_H_
#define TRAJ_H_

typedef enum { TURN,
				 DISPLACEMENT}Move_type;

typedef enum { INITIAL_TURN,
				  CRUISE,
				  STOPPED}Move_state;

class Navigator{
public:
	Navigator();
	void move_to(float x, float y);
	void turn_to(float x, float y);
	float compute_cons_speed();
	float compute_cons_omega();
	void update();
	bool isTrajectoryFinished();

private:
	bool turn_done;
	bool displacement_done;
	bool trajectory_done;
	float x_target;
	float y_target;
	Move_type move_type;
	Move_state move_state;

	float center_axes(float angle);
	float center_radian(float angle);
	int scalaire(float x,float y,float x2,float y2);
};

extern Navigator navigator;

#endif /* TRAJ_H_ */
