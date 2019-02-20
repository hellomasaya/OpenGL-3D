#include "main.h"
#include "timer.h"
#include "airplane.h"
#include "ocean.h"
#include "ball.h"
#include "volcano.h"
#include "checkpoint.h"
#include "arrow.h"
#include "diamond.h"
#include "ring.h"
#include "sphere.h"
#include "dashboard.h"
#include "parachute.h"
#include "compass.h"
#include "pool.h"


using namespace std;

GLMatrices Matrices;
GLMatrices Matrices2;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

Ball ball1;
Compass compass;
Pool pool;

Ocean ocean;
Arrow arrow[10], startarrow[10];
Parachute parachute[15];
Airplane airplane;
Volcano volcano[5];
Dashboard A1, A2, A3, A4, A5, A6, A7;
Dashboard A11, A12, A13, A14, A15, A16, A17;
Dashboard F1, F2, F3, F4, F5, F6, F7;
Dashboard F11, F12, F13, F14, F15, F16, F17;
Dashboard Ch1, Ch2, Ch3, Ch4, Ch5, Ch6, Ch7;
Dashboard Ch11, Ch12, Ch13, Ch14, Ch15, Ch16, Ch17;
vector<Sphere> sphere, missile, bomb;
Checkpoint checkpoint[8];
Diamond diamond[5];
Ring ring[3];
int check[8] ={0};
int t=0;
long long sphere_count=1;
bool sphere_hold=false;
bool bomb_hold=false;
int feul = 60;
int checks=8;
int crash=0, alt=0;;

const long int one = 1;
const long int zero = 0;
const double onef = 1.0f;
float screen_zoom = 0.05f, screen_center_x = 0, screen_center_y = 0;
// float camera_rotation_angle = 100;
float camera_rotation_angle = 95.0*onef;

int camera = 0;
float eye_x,eye_y,eye_z;
float target_x,target_y,target_z;


Timer t60(1.0 / 60);

float RandomNumber(float Min, float Max)
{
    return ((float(rand()) / float(RAND_MAX)) * (Max - Min)) + Min;
}

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {

    if (camera == 0){
        //FOLLOW
		target_x = onef*airplane.position.x;
        // -3*sin(airplane.rotation* M_PI / 360.0f);
		target_y = onef*airplane.position.y;
		target_z = onef*airplane.position.z+1;
        // -3*cos(airplane.rotation* M_PI / 360.0f);
		camera_rotation_angle = -airplane.rotation + 95;

		eye_x = onef*target_x +7*sin(airplane.rotation* M_PI / 360.0f);
		eye_y = onef*target_y+3; 
		eye_z = onef*target_z+2+7*cos(airplane.rotation* M_PI / 360.0f);

        // target_x = onef*airplane.position.x;
		// target_y = onef*airplane.position.y;
		// target_z = onef*airplane.position.z+1;
		// camera_rotation_angle = -airplane.rotation + 95;

		// eye_x = onef*target_x ;
		// eye_y = onef*target_y+6; 
		// eye_z = onef*target_z+6;

	}

    else if (camera == 1){
        //TOP
		target_x = onef*airplane.position.x;
		target_y = onef*airplane.position.y;
		target_z = onef*airplane.position.z;
		// camera_rotation_angle = -airplane.rotation + 95;

		eye_x = onef*target_x+ 1*sin(airplane.rotation*M_PI/360.0f*onef);
		eye_y = onef*target_y + 10;
		eye_z = onef*target_z + 0.1+ 1*cos(airplane.rotation*M_PI/360.0f*onef);

	}

    else if (camera == 2){
        // TOWER
		target_x = onef*airplane.position.x;
		target_y = onef*airplane.position.y;
		target_z = onef*airplane.position.z;
		// camera_rotation_angle = -airplane.rotation + 95;

		eye_x = onef*target_x + 30*one;
		eye_y = onef*target_y + 30*one;
		eye_z = onef*target_z + 30*one;

	}

    else if (camera == 3){
        //PLANE
		target_x = onef*airplane.position.x-1.5*sin(airplane.rotation* M_PI / 360.0f);
		target_y = onef*airplane.position.y;
		target_z = onef*airplane.position.z-7-1.5*cos(airplane.rotation* M_PI / 360.0f);
		camera_rotation_angle = -airplane.rotation + 95;

		eye_x = airplane.position.x+1.5*sin(airplane.rotation* M_PI / 360.0f);
		eye_y = airplane.position.y;
		eye_z = airplane.position.z -2+1.5*cos(airplane.rotation* M_PI / 360.0f);

	}

    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    // Eye - Location of camera. Don't change unless you are sure!!
    // glm::vec3 eye(eye_x, eye_y, eye_z);
    // // Target - Where is the camera looking at.  Don't change unless you are sure!!
    // glm::vec3 target (target_x, target_y, target_z);
    // // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    // glm::vec3 up (0, 1, 0);
    glm::vec3 eye (onef*eye_x,onef*eye_y,onef*eye_z);
    glm::vec3 eye2 (-3,6,4);
	// Target - Where is the camera looking at.  Don't change unless you are sure!!
	glm::vec3 target (onef*target_x, onef*target_y, onef*target_z);
	glm::vec3 target2 (-3,6,0);
	// Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
	glm::vec3 up (zero, one, zero);

    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D

    Matrices2.view = glm::lookAt( eye2, target2, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;
    glm::mat4 VP2 = Matrices2.projection * Matrices2.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    // glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    glm::mat4 MVP;  // MVP = Projection * View * Model
    glm::mat4 MVP2;  // MVP = Projection * View * Model
	// Scene render
	ocean.draw(VP);
    pool.draw(VP);

    airplane.draw(VP);
    for(int i=0; i<10; i++){
        startarrow[i].draw(VP);
    }
    for(int i=0; i<5; i++){
        volcano[i].draw(VP);
        diamond[i].draw(VP);
    }
    for(int i=0; i<15; i++){
        parachute[i].draw(VP);
    }
    for(int i=0; i<2; i++){
        ring[i].draw(VP);
    }
    for(int i=0; i<8; i++){
        checkpoint[i].draw(VP);
        arrow[i].draw(VP);
    }

    vector<Sphere> :: iterator s;
	s = sphere.begin();
	while (s < sphere.end()) {
		s->draw(VP);
		++s;
	}

    vector<Sphere> :: iterator m;
	m = missile.begin();
	while (m < missile.end()) {
		m->draw(VP);
		++m;
	}

    vector<Sphere> :: iterator bo;
	bo = bomb.begin();
	while (bo < bomb.end()) {
		bo->draw(VP);
		++bo;
	}
    
    t+=1;
    if(t%60==0){
        t=1;
        int j=0;
        for(int i=0; i<8; i++){
            if(check[i]==0){
                if(sphere_count%3==1){
                    Sphere new_sphere = Sphere(checkpoint[i].position.x*one ,checkpoint[i].position.y*one + 1,checkpoint[i].position.z*one -1, COLOR_BLACK);
		            new_sphere.speed = -0.1f*onef;
		            new_sphere.yspeed = 0.2f*onef;
                    sphere.push_back(new_sphere);
                    sphere_count++;
                }
                else if(sphere_count%3==0){
                    Sphere new_sphere = Sphere(checkpoint[i].position.x*one ,checkpoint[i].position.y*one + 1,checkpoint[i].position.z*one -1, COLOR_BLACK);
		            new_sphere.speed = 0.1f*onef;
		            new_sphere.yspeed = RandomNumber(0.1f, 0.4f)*onef;
                    sphere.push_back(new_sphere);
                    sphere_count++;
                }
                else if(sphere_count%3==2){
                    Sphere new_sphere = Sphere(checkpoint[i].position.x*one ,checkpoint[i].position.y*one + 1,checkpoint[i].position.z*one -1, COLOR_BLACK);
		            new_sphere.speed = -0.1f*onef;
		            new_sphere.yspeed = 0.2f*onef;
                    sphere.push_back(new_sphere);
                    sphere_count++;
                }
            }
        }
    }

    long long int tmp_alt=alt;
    int dig0=tmp_alt%10;
    tmp_alt/=10;
    int dig1=tmp_alt%10;
    bool binary0[5];
    bool binary1[5];
    int bin0[5];
    int bin1[5];
    for(int i=0;i<=4;i++){
           binary0[i]=false;
           binary1[i]=false;
           bin0[i]=0;
           bin1[i]=0;
    }
    int idx0=0;
    while(dig0>0){
        bin0[idx0]=dig0%2;
        dig0/=2;
        idx0++;
    }
    int idx1=0;
    while(dig1>0){
        bin1[idx1]=dig1%2;
        dig1/=2;
        idx1++;
    }
    for(int i=0;i<4;i++)
    {
        if(bin0[3-i])
            binary0[i]=true;
        else binary0[i]=false;
        if(bin1[3-i])
            binary1[i]=true;
        else binary1[i]=false;
    }
    ball1.draw(VP2);

    if(alt >=0.0){
        if((binary0[0] || binary0[2] || (binary0[1]&&binary0[3]) || ((!(binary0[1]))&&(!(binary0[3]))) ))
            A1.draw(VP2);
        if(((!binary0[1]) || (binary0[2]&&binary0[3]) || ((!binary0[2])&&(!binary0[3])) ))
                A2.draw(VP2);
        if((binary0[1] || (!binary0[2]) || binary0[3] ))
                A3.draw(VP2);
        if(((((!binary0[3])&&binary0[2]) || ((!(binary0[1]))&&(!(binary0[3])))) || (((!binary0[2])&&binary0[1]&&binary0[3]) || ((!(binary0[1]))&&((binary0[2]))) || binary0[0] )))
                A4.draw(VP2);
        if((((!binary0[3])&&binary0[2]) || ((!(binary0[1]))&&(!(binary0[3]))) ))
                A5.draw(VP2);
        if((binary0[0] || (((!binary0[2]))&&(!(binary0[3]))) || (((binary0[1]))&&(!(binary0[2]))) ||(((binary0[1]))&&(!(binary0[3]))) ))
                A6.draw(VP2);
        if((binary0[0] || (((binary0[1]))&&(!(binary0[2]))) || ((!(binary0[1]))&&((binary0[2]))) ||(((binary0[2]))&&(!(binary0[3]))) ))
                A7.draw(VP2);
            
        if((binary1[0] || binary1[2] || (binary1[1]&&binary1[3]) || ((!(binary1[1]))&&(!(binary1[3]))) ))
            A11.draw(VP2);
        // // bool bb0=((~binary1[1]) | (binary1[2]&binary1[3]) | ((~binary1[2])&(~binary1[3])) );
        if(((!binary1[1]) || (binary1[2]&&binary1[3]) || ((!binary1[2])&&(!binary1[3])) ))
                A12.draw(VP2);
        if((binary1[1] || (!binary1[2]) || binary1[3] ))
                A13.draw(VP2);
        if(((((!binary1[3])&&binary1[2]) || ((!(binary1[1]))&&(!(binary1[3])))) || (((!binary1[2])&&binary1[1]&&binary1[3]) || ((!(binary1[1]))&&((binary1[2]))) || binary1[0] )))
                A14.draw(VP2);
        if((((!binary1[3])&&binary1[2]) || ((!(binary1[1]))&&(!(binary1[3]))) ))
                A15.draw(VP2);
        if((binary1[0] || (((!binary1[2]))&&(!(binary1[3]))) || (((binary1[1]))&&(!(binary1[2]))) ||(((binary1[1]))&&(!(binary1[3]))) ))
                A16.draw(VP2);
        if((binary1[0] || (((binary1[1]))&&(!(binary1[2]))) || ((!(binary1[1]))&&((binary1[2]))) ||(((binary1[2]))&&(!(binary1[3]))) ))
                A17.draw(VP2); 
    }
    
    else
    {
        A7.draw(VP2);
        A17.draw(VP2);
    }

    //check-points left
    long long int tmp_checks=checks;
    int digc0=tmp_checks%10;
    tmp_checks/=10;
    int digc1=tmp_checks%10;
    bool cbinary0[5];
    bool cbinary1[5];
    int cbin0[5];
    int cbin1[5];
    for(int i=0;i<=4;i++){
           cbinary0[i]=false;
           cbinary1[i]=false;
           cbin0[i]=0;
           cbin1[i]=0;
    }
    int idxc0=0;
    while(digc0>0){
        cbin0[idxc0]=digc0%2;
        digc0/=2;
        idxc0++;
    }
    int idxc1=0;
    while(digc1>0){
        cbin1[idxc1]=digc1%2;
        digc1/=2;
        idxc1++;
    }
    for(int i=0;i<4;i++)
    {
        if(cbin0[3-i])
            cbinary0[i]=true;
        else cbinary0[i]=false;
        if(cbin1[3-i])
            cbinary1[i]=true;
        else cbinary1[i]=false;
    }

    if(checks >=0){
        if((cbinary0[0] || cbinary0[2] || (cbinary0[1]&&cbinary0[3]) || ((!(cbinary0[1]))&&(!(cbinary0[3]))) ))
            Ch1.draw(VP2);
        if(((!cbinary0[1]) || (cbinary0[2]&&cbinary0[3]) || ((!cbinary0[2])&&(!cbinary0[3])) ))
                Ch2.draw(VP2);
        if((cbinary0[1] || (!cbinary0[2]) || cbinary0[3] ))
                Ch3.draw(VP2);
        if(((((!cbinary0[3])&&cbinary0[2]) || ((!(cbinary0[1]))&&(!(cbinary0[3])))) || (((!cbinary0[2])&&cbinary0[1]&&cbinary0[3]) || ((!(cbinary0[1]))&&((cbinary0[2]))) || cbinary0[0] )))
                Ch4.draw(VP2);
        if((((!cbinary0[3])&&cbinary0[2]) || ((!(cbinary0[1]))&&(!(cbinary0[3]))) ))
                Ch5.draw(VP2);
        if((cbinary0[0] || (((!cbinary0[2]))&&(!(cbinary0[3]))) || (((cbinary0[1]))&&(!(cbinary0[2]))) ||(((cbinary0[1]))&&(!(cbinary0[3]))) ))
                Ch6.draw(VP2);
        if((cbinary0[0] || (((cbinary0[1]))&&(!(cbinary0[2]))) || ((!(cbinary0[1]))&&((cbinary0[2]))) ||(((cbinary0[2]))&&(!(cbinary0[3]))) ))
                Ch7.draw(VP2);
            
        if((cbinary1[0] || cbinary1[2] || (cbinary1[1]&&cbinary1[3]) || ((!(cbinary1[1]))&&(!(cbinary1[3]))) ))
            Ch11.draw(VP2);
        // // bool bb0=((~cbinary1[1]) | (cbinary1[2]&cbinary1[3]) | ((~cbinary1[2])&(~cbinary1[3])) );
        if(((!cbinary1[1]) || (cbinary1[2]&&cbinary1[3]) || ((!cbinary1[2])&&(!cbinary1[3])) ))
                Ch12.draw(VP2);
        if((cbinary1[1] || (!cbinary1[2]) || cbinary1[3] ))
                Ch13.draw(VP2);
        if(((((!cbinary1[3])&&cbinary1[2]) || ((!(cbinary1[1]))&&(!(cbinary1[3])))) || (((!cbinary1[2])&&cbinary1[1]&&cbinary1[3]) || ((!(cbinary1[1]))&&((cbinary1[2]))) || cbinary1[0] )))
                Ch14.draw(VP2);
        if((((!cbinary1[3])&&cbinary1[2]) || ((!(cbinary1[1]))&&(!(cbinary1[3]))) ))
                Ch15.draw(VP2);
        if((cbinary1[0] || (((!cbinary1[2]))&&(!(cbinary1[3]))) || (((cbinary1[1]))&&(!(cbinary1[2]))) ||(((cbinary1[1]))&&(!(cbinary1[3]))) ))
                Ch16.draw(VP2);
        if((cbinary1[0] || (((cbinary1[1]))&&(!(cbinary1[2]))) || ((!(cbinary1[1]))&&((cbinary1[2]))) ||(((cbinary1[2]))&&(!(cbinary1[3]))) ))
                Ch17.draw(VP2); 
    }
    
    else
    {
        Ch7.draw(VP2);
        Ch17.draw(VP2);
    }


    //fuel left
    long long int tmp_feul=feul;
    int digf0=tmp_feul%10;
    tmp_feul/=10;
    int digf1=tmp_feul%10;
    bool fbinary0[5];
    bool fbinary1[5];
    int fbin0[5];
    int fbin1[5];
    for(int i=0;i<=4;i++){
           fbinary0[i]=false;
           fbinary1[i]=false;
           fbin0[i]=0;
           fbin1[i]=0;
    }
    int idxf0=0;
    while(digf0>0){
        fbin0[idxf0]=digf0%2;
        digf0/=2;
        idxf0++;
    }
    int idxf1=0;
    while(digf1>0){
        fbin1[idxf1]=digf1%2;
        digf1/=2;
        idxf1++;
    }
    for(int i=0;i<4;i++)
    {
        if(fbin0[3-i])
            fbinary0[i]=true;
        else fbinary0[i]=false;
        if(fbin1[3-i])
            fbinary1[i]=true;
        else fbinary1[i]=false;
    }

    if(feul >=0){
        if((fbinary0[0] || fbinary0[2] || (fbinary0[1]&&fbinary0[3]) || ((!(fbinary0[1]))&&(!(fbinary0[3]))) ))
            F1.draw(VP2);
        if(((!fbinary0[1]) || (fbinary0[2]&&fbinary0[3]) || ((!fbinary0[2])&&(!fbinary0[3])) ))
                F2.draw(VP2);
        if((fbinary0[1] || (!fbinary0[2]) || fbinary0[3] ))
                F3.draw(VP2);
        if(((((!fbinary0[3])&&fbinary0[2]) || ((!(fbinary0[1]))&&(!(fbinary0[3])))) || (((!fbinary0[2])&&fbinary0[1]&&fbinary0[3]) || ((!(fbinary0[1]))&&((fbinary0[2]))) || fbinary0[0] )))
                F4.draw(VP2);
        if((((!fbinary0[3])&&fbinary0[2]) || ((!(fbinary0[1]))&&(!(fbinary0[3]))) ))
                F5.draw(VP2);
        if((fbinary0[0] || (((!fbinary0[2]))&&(!(fbinary0[3]))) || (((fbinary0[1]))&&(!(fbinary0[2]))) ||(((fbinary0[1]))&&(!(fbinary0[3]))) ))
                F6.draw(VP2);
        if((fbinary0[0] || (((fbinary0[1]))&&(!(fbinary0[2]))) || ((!(fbinary0[1]))&&((fbinary0[2]))) ||(((fbinary0[2]))&&(!(fbinary0[3]))) ))
                F7.draw(VP2);
            
        if((fbinary1[0] || fbinary1[2] || (fbinary1[1]&&fbinary1[3]) || ((!(fbinary1[1]))&&(!(fbinary1[3]))) ))
            F11.draw(VP2);
        // // bool bb0=((~fbinary1[1]) | (fbinary1[2]&fbinary1[3]) | ((~fbinary1[2])&(~fbinary1[3])) );
        if(((!fbinary1[1]) || (fbinary1[2]&&fbinary1[3]) || ((!fbinary1[2])&&(!fbinary1[3])) ))
                F12.draw(VP2);
        if((fbinary1[1] || (!fbinary1[2]) || fbinary1[3] ))
                F13.draw(VP2);
        if(((((!fbinary1[3])&&fbinary1[2]) || ((!(fbinary1[1]))&&(!(fbinary1[3])))) || (((!fbinary1[2])&&fbinary1[1]&&fbinary1[3]) || ((!(fbinary1[1]))&&((fbinary1[2]))) || fbinary1[0] )))
                F14.draw(VP2);
        if((((!fbinary1[3])&&fbinary1[2]) || ((!(fbinary1[1]))&&(!(fbinary1[3]))) ))
                F15.draw(VP2);
        if((fbinary1[0] || (((!fbinary1[2]))&&(!(fbinary1[3]))) || (((fbinary1[1]))&&(!(fbinary1[2]))) ||(((fbinary1[1]))&&(!(fbinary1[3]))) ))
                F16.draw(VP2);
        if((fbinary1[0] || (((fbinary1[1]))&&(!(fbinary1[2]))) || ((!(fbinary1[1]))&&((fbinary1[2]))) ||(((fbinary1[2]))&&(!(fbinary1[3]))) ))
                F17.draw(VP2); 
    }
    
    else
    {
        F7.draw(VP2);
        F17.draw(VP2);
    }

	compass.draw(VP2);

}

void tick_input(GLFWwindow *window) {

    //airplane movement
    int forward = glfwGetKey(window, GLFW_KEY_UP);
    int back = glfwGetKey(window, GLFW_KEY_DOWN);
    int up = glfwGetKey(window, GLFW_KEY_W);
    int down = glfwGetKey(window, GLFW_KEY_S);
    //rotate
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    //roll
    int clockwise = glfwGetKey(window, GLFW_KEY_A);
    int counterclockwise = glfwGetKey(window, GLFW_KEY_D);
    //missiles and grenade
    int mi = glfwGetKey(window, GLFW_KEY_M);
    int g = glfwGetKey(window, GLFW_KEY_G);

    if(left && crash==0) {
        airplane.rotation +=1;
    }
    if(right&& crash==0){
        airplane.rotation -=1;
    }
    if(forward&& crash==0){
        airplane.position.z -=0.2*cos(airplane.rotation * M_PI / 360.0f);
        airplane.position.x -=0.2*sin(airplane.rotation * M_PI / 360.0f);
    }
    if(back&& crash==0){
        airplane.position.z +=0.2*cos(airplane.rotation * M_PI / 360.0f);
        airplane.position.x +=0.2*sin(airplane.rotation * M_PI / 360.0f);
    }
    if(clockwise&& crash==0){
        airplane.roll +=0.5;
    }
    if(counterclockwise&& crash==0){
        airplane.roll -=0.5;
    }
    if(up&& crash==0){
        airplane.position.y += 0.1;
    }
    if(down&& crash==0){
        airplane.position.y -= 0.1;
    }

    if(mi*one && sphere_hold ==false && crash==0){
        sphere_hold=true;
		Sphere new_miss = Sphere(airplane.position.x*one ,airplane.position.y*one + 1,airplane.position.z*one -1, COLOR_LIGHT_ORANGE);
		new_miss.speed = 1.0f*onef - 0.85;
		new_miss.yspeed = 0.05f*onef;
		new_miss.rotation = -airplane.rotation*one;
		missile.push_back(new_miss);
	}

    if(g*one && bomb_hold ==false&& crash==0){
        bomb_hold=true;
		Sphere new_bo = Sphere(airplane.position.x*one ,airplane.position.y*one -2,airplane.position.z*one -1, COLOR_GRENADE);
		new_bo.speed = 1.0f*onef - 0.96;
		new_bo.yspeed = 0.05f*onef;
		new_bo.rotation = -airplane.rotation*one;
		bomb.push_back(new_bo);
	}

    //views
	int follow  = one*glfwGetKey(window, GLFW_KEY_1*one);
    int top   = one*glfwGetKey(window, GLFW_KEY_2*one);
	int tower  = one*glfwGetKey(window, GLFW_KEY_3*one);
	int plane  = one*glfwGetKey(window, GLFW_KEY_4*one);
    //Follow
    if(one*follow){
        camera=0;
    }
    //Top
    if(one*top){
        camera=1;
    }

    if(one*tower){
        camera=2;
    }

    if(one*plane){
        camera=3;
    }

}

void tick_elements() {
    // cout << airplane.rotation << endl;
    airplane.tick();
    ocean.tick();
    for(int i=0; i<5; i++){
        volcano[i].tick();
        diamond[i].tick();
    }
    for(int i=0; i<15; i++){
        parachute[i].tick();
    }
    for(int i=0; i<8; i++){
        checkpoint[i].tick();
        arrow[i].tick();
    }
    alt=airplane.position.y;

    if(airplane.position.y <= 0.0f){
        crash =1;
        airplane.position.y = 1.0f;
        printf("CRASH: ALT\n");
    }
    if(feul<=0){
        crash=1;
        printf("CRASH: NO FEUL\n");
        airplane.position.y = 1.0f;
    }
    //Detect Collisions ////////////////////////

    vector<Sphere> :: iterator s;
	s = sphere.begin();
	while ( s < sphere.end()) {
		if(s->tick())
			sphere.erase(s);
        else if(detect_collision(airplane.bounding_box(),s->bounding_box())){
            feul -=10;
            sphere.erase(s);
            printf("Fireball Hit!\n");
        }
		++s;
	}

    vector<Sphere> :: iterator m;
	m = missile.begin();
	while ( m < missile.end()) {
		if(m->tick())
			missile.erase(m);
        else if(true){
            for(int i =0; i<8; i++){
                if(detect_collision(checkpoint[i].bounding_box(),m->bounding_box())){
                    checks -=1;
                    check[i]=1;
                    missile.erase(m);
                    arrow[i].position.y = -20.0f;
                    checkpoint[i].position.y = -20.0f;
                    printf("Checkpoint conquered!\n");
                }
                else if(detect_collision(parachute[i].bounding_box(),m->bounding_box())){
                    missile.erase(m);
                    parachute[i].position.y = -20.0f;
                    feul+=2;
                    printf("Enemy killed!\n");
                }
            }
        }
		++m;
	}

    vector<Sphere> :: iterator bo;
	bo = bomb.begin();
	while ( bo < bomb.end()) {
		if(bo->tick())
			bomb.erase(bo);
        else if(true){
            for(int i =0; i<8; i++){
                if(detect_collision(checkpoint[i].bounding_box(),bo->bounding_box())){
                    checks -=1;
                    check[i]=1;
                    bomb.erase(bo);
                    arrow[i].position.y = -20.0f;
                    checkpoint[i].position.y = -20.0f;
                    printf("Checkpoint conquered!\n");
                }
            }
        }
		++bo;
	}
    // Fuelup Collision With Plane
	int fc = zero;
	while (fc < 5) {
		if(detect_collision(airplane.bounding_box(),diamond[fc].bounding_box())){
			printf("FUEL!\n");
            airplane.position.z +=1*cos(airplane.rotation * M_PI / 360.0f);
            airplane.position.x +=1*sin(airplane.rotation * M_PI / 360.0f);
            diamond[fc].position.y = -15.0f;
			feul +=10;
		}
		++fc;
	}

    int pc = zero;
	while (pc < 15) {
		if(detect_collision(airplane.bounding_box(),parachute[pc].bounding_box())){
			printf("Enemy!\n");
            airplane.position.z +=1*cos(airplane.rotation * M_PI / 360.0f);
            airplane.position.x +=1*sin(airplane.rotation * M_PI / 360.0f);
            parachute[pc].position.y = -15.0f;
			feul -=5;
		}
		++pc;
	}

    // Fuelup Collision- Ring With Plane
	int rc = zero;
	while (rc < 2) {
		if(detect_collision(airplane.bounding_box(),ring[rc].bounding_box())){
			printf("FEUL!\n");
            ring[rc].position.y = -25.0f;
			feul +=50;
		}
		++rc;
	}

    // Volcano Collision With Plane
	int vc = zero;
	while (vc < 5) {
		if(detect_collision(airplane.bounding_box(),volcano[vc].bounding_box())){
			printf("NO FLYING ZONE!\n");
            quit(window);
		}
		++vc;
	}

    if(alt >=0.0){
        A1.tick();
        A2.tick();
        A3.tick();
        A4.tick();
        A5.tick();
        A6.tick();
        A7.tick();
        A11.tick();
        A12.tick();
        A13.tick();
        A14.tick();
        A15.tick();
        A16.tick();
        A17.tick();
    }
        F1.tick();
        F2.tick();
        F3.tick();
        F4.tick();
        F5.tick();
        F6.tick();
        F7.tick();
        F11.tick();
        F12.tick();
        F13.tick();
        F14.tick();
        F15.tick();
        F16.tick();
        F17.tick();

        Ch1.tick();
        Ch2.tick();
        Ch3.tick();
        Ch4.tick();
        Ch5.tick();
        Ch6.tick();
        Ch7.tick();
        Ch11.tick();
        Ch12.tick();
        Ch13.tick();
        Ch14.tick();
        Ch15.tick();
        Ch16.tick();
        Ch17.tick();

    compass.rotation=-airplane.rotation;
    compass.tick();


}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models
    ball1 = Ball(0.0, 1.0, COLOR_BLACK);
    ocean = Ocean(0, -12+3, 0,COLOR_OCEAN);
    airplane = Airplane(0, 13, 100, COLOR_AIRPLANE1);
    compass = Compass(-5.0, -60.0, 0, COLOR_AIRPLANE1);
    pool = Pool(0,0, COLOR_OCEAN);
    pool.position.y -= 12343;

    for(int i=0; i<5; i++){
    startarrow[i] = Arrow(2*i, 3, 87, COLOR_ARROW1);
    startarrow[i].rotation = 90;
    }
    for(int i=5; i<10; i++){
    startarrow[i] = Arrow(-2*i+8, 3, 87, COLOR_ARROW1);
    startarrow[i].rotation = 90;
    }
    for(int i=0; i<5; i++){
        float x = RandomNumber(-50.0f, 50.0f);
        float z = RandomNumber(-100.0f, 50.0f);
        float dx = RandomNumber(-30.0f, 30.0f);
        float dy = RandomNumber(2.0f, 15.0f);
        float dy2 = RandomNumber(32.0f, 75.0f);
        float dz = RandomNumber(-70.0f, 10.0f);
        volcano[i] = Volcano(x,0.1+3, z, COLOR_AIRPLANE1);
        diamond[i] = Diamond(dx, dy+3, dz, COLOR_FEULUP1);

    }
    for(int i=0; i<15; i++){
        float dx = RandomNumber(-30.0f, 30.0f);
        float dy2 = RandomNumber(32.0f, 75.0f);
        float dz = RandomNumber(-70.0f, 10.0f);
        parachute[i] = Parachute(dx+i, dy2+3, dz, COLOR_FEULUP1);
        parachute[i].speed = 0.07;
    }

    for(int i=0; i<4; i++){
        float c_x = RandomNumber(-50.0f, 50.0f);
        checkpoint[i] = Checkpoint(c_x, 0.1+3, -20*i, COLOR_CHECK2);
        arrow[i] = Arrow(c_x, 8.0+3, -20*i, COLOR_ARROW1);
    }

    float r_x = RandomNumber(-50.0f, 50.0f);
    float r_z = RandomNumber(-30.0f, -70.0f);
    ring[0] = Ring(r_x, 10+3, r_z, COLOR_CHECK2);
    ring[1] = Ring(r_x, 10+3, r_z+45, COLOR_CHECK2);
    

    for(int i=4; i<8; i++){
        float c_x = RandomNumber(-50.0f, 50.0f);
        checkpoint[i] = Checkpoint(c_x, 0.1+3, 8*i, COLOR_CHECK2);
        arrow[i] = Arrow(c_x, 8.0+3, 8*i, COLOR_ARROW1);
    }
    double dx1=-25.0, dy1=-53.5;
    A1 = Dashboard(-5.5+dx1,8.5+dy1,0, COLOR_WHITE);
    A2 = Dashboard(-5.8+dx1,7.9+dy1,0, COLOR_WHITE);
    A3 = Dashboard(-5.8+dx1,4.6+dy1,0, COLOR_WHITE);
    A4 = Dashboard(-5.5+dx1,1.3+dy1,0, COLOR_WHITE);
    A5 = Dashboard(-8.5+dx1,4.6+dy1,0, COLOR_WHITE);
    A6 = Dashboard(-8.5+dx1,7.9+dy1,0, COLOR_WHITE);
    A7 = Dashboard(-5.5+dx1,4.8+dy1,0, COLOR_WHITE);
    A2.rotation=90;
    A3.rotation=90;
    A5.rotation=90;
    A6.rotation=90;

    double dx2=-30.0, dy2=-53.5;
    A11 = Dashboard(-5.5+dx2,8.5+dy2,0, COLOR_WHITE);
    A12 = Dashboard(-5.8+dx2,7.9+dy2,0, COLOR_WHITE);
    A13 = Dashboard(-5.8+dx2,4.6+dy2,0, COLOR_WHITE);
    A14 = Dashboard(-5.5+dx2,1.3+dy2,0, COLOR_WHITE);
    A15 = Dashboard(-8.5+dx2,4.6+dy2,0, COLOR_WHITE);
    A16 = Dashboard(-8.5+dx2,7.9+dy2,0, COLOR_WHITE);
    A17 = Dashboard(-5.5+dx2,4.8+dy2,0, COLOR_WHITE);
    A12.rotation=90;
    A13.rotation=90;
    A15.rotation=90;
    A16.rotation=90;

    double fdx1=5.0, fdy1=-53.5;
    F1 = Dashboard(-5.5+fdx1,8.5+fdy1,0, COLOR_WHITE);
    F2 = Dashboard(-5.8+fdx1,7.9+fdy1,0, COLOR_WHITE);
    F3 = Dashboard(-5.8+fdx1,4.6+fdy1,0, COLOR_WHITE);
    F4 = Dashboard(-5.5+fdx1,1.3+fdy1,0, COLOR_WHITE);
    F5 = Dashboard(-8.5+fdx1,4.6+fdy1,0, COLOR_WHITE);
    F6 = Dashboard(-8.5+fdx1,7.9+fdy1,0, COLOR_WHITE);
    F7 = Dashboard(-5.5+fdx1,4.8+fdy1,0, COLOR_WHITE);
    F2.rotation=90;
    F3.rotation=90;
    F5.rotation=90;
    F6.rotation=90;

    double fdx2=0.0, fdy2=-53.5;
    F11 = Dashboard(-5.5+fdx2,8.5+fdy2,0, COLOR_WHITE);
    F12 = Dashboard(-5.8+fdx2,7.9+fdy2,0, COLOR_WHITE);
    F13 = Dashboard(-5.8+fdx2,4.6+fdy2,0, COLOR_WHITE);
    F14 = Dashboard(-5.5+fdx2,1.3+fdy2,0, COLOR_WHITE);
    F15 = Dashboard(-8.5+fdx2,4.6+fdy2,0, COLOR_WHITE);
    F16 = Dashboard(-8.5+fdx2,7.9+fdy2,0, COLOR_WHITE);
    F17 = Dashboard(-5.5+fdx2,4.8+fdy2,0, COLOR_WHITE);
    F12.rotation=90;
    F13.rotation=90;
    F15.rotation=90;
    F16.rotation=90;

    double cdx1=30.0, cdy1=-53.5;
    Ch1 = Dashboard(-5.5+cdx1,8.5+cdy1,0, COLOR_WHITE);
    Ch2 = Dashboard(-5.8+cdx1,7.9+cdy1,0, COLOR_WHITE);
    Ch3 = Dashboard(-5.8+cdx1,4.6+cdy1,0, COLOR_WHITE);
    Ch4 = Dashboard(-5.5+cdx1,1.3+cdy1,0, COLOR_WHITE);
    Ch5 = Dashboard(-8.5+cdx1,4.6+cdy1,0, COLOR_WHITE);
    Ch6 = Dashboard(-8.5+cdx1,7.9+cdy1,0, COLOR_WHITE);
    Ch7 = Dashboard(-5.5+cdx1,4.8+cdy1,0, COLOR_WHITE);
    Ch2.rotation=90;
    Ch3.rotation=90;
    Ch5.rotation=90;
    Ch6.rotation=90;

    double cdx2=25.0, cdy2=-53.5;
    Ch11 = Dashboard(-5.5+cdx2,8.5+cdy2,0, COLOR_WHITE);
    Ch12 = Dashboard(-5.8+cdx2,7.9+cdy2,0, COLOR_WHITE);
    Ch13 = Dashboard(-5.8+cdx2,4.6+cdy2,0, COLOR_WHITE);
    Ch14 = Dashboard(-5.5+cdx2,1.3+cdy2,0, COLOR_WHITE);
    Ch15 = Dashboard(-8.5+cdx2,4.6+cdy2,0, COLOR_WHITE);
    Ch16 = Dashboard(-8.5+cdx2,7.9+cdy2,0, COLOR_WHITE);
    Ch17 = Dashboard(-5.5+cdx2,4.8+cdy2,0, COLOR_WHITE);
    Ch12.rotation=90;
    Ch13.rotation=90;
    Ch15.rotation=90;
    Ch16.rotation=90;
    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");
    Matrices2.MatrixID = glGetUniformLocation(programID, "MVP2");
    Matrices.Transparency = glGetUniformLocation(programID, "trans");

    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    srand(time(0));
    int width  = 600;
    int height = 600;

    window = initGLFW(width, height);

    initGL (window, width, height);

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {
            if(t%50*one == zero)
			{	
                feul-=1;
				sphere_hold = false;
				bomb_hold = false;
			}
            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            tick_elements();
            tick_input(window);
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
	return (abs(a.x - b.x) * 2 *one <= (a.width + b.width)) &&
		   (abs(a.y - b.y) * 2 *one<= (a.height + b.height)) &&
		   (abs(a.z - b.z) * 2 *one<= (a.depth + b.depth));
}

void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    Matrices2.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
    Matrices.projection = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 100.0f);
}