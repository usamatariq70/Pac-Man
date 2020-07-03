#include <windows.h>
#include <GL\freeglut.h>
#include <cmath>

int object[4][2] = {{24, 28}, {26, 28}, {26, 26}, {24, 26}};
int food[20][2] = {{2, 28}, {46, 28}, {14, 46}, {25, 33}, {46, 12}, {10, 45}, {4, 12}, {43, 36}, {46, 28}, {4, 40}, {40, 40}, {30, 22}, {40, 4}, {3, 10}, {3, 25}, {40, 25}, {46, 46}, {32, 30}, {10, 36}, {38, 38}};
int a = food[2][0], b = food[2][1];
int c = 0;
int score = 0;

void init(){
   glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0,50,0,50,-1,1);
    glMatrixMode(GL_MODELVIEW);
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_QUADS);//object
    glColor3f(1.0, 0.0, 0.0);
    glVertex2f(object[0][0], object[0][1]);
    glVertex2f(object[1][0], object[1][1]);
    glVertex2f(object[2][0], object[2][1]);
    glVertex2f(object[3][0], object[3][1]);
    glEnd();

    glBegin(GL_QUADS);//bottom MID WALL
    glColor3f(1.0,1.0,1.0);
    glVertex2f(12,20);
    glVertex2f(36,20);
    glVertex2f(36,18);
    glVertex2f(12,18);
    glEnd();

    glBegin(GL_QUADS);//up MID WALL
    glColor3f(1.0,1.0,1.0);
    glVertex2f(12,36);
    glVertex2f(36,36);
    glVertex2f(36,34);
    glVertex2f(12,34);
    glEnd();

    glBegin(GL_QUADS);//LEFT UP OBSTACLE
    glColor3f(1.0,1.0,1.0);
    glVertex2f(6,44);
    glVertex2f(8,44);
    glVertex2f(8,38);
    glVertex2f(6,38);
    glEnd();

    glBegin(GL_QUADS);//LEFT DOWN OBSTACLE
    glColor3f(1.0,1.0,1.0);
    glVertex2f(6,16);
    glVertex2f(8,16);
    glVertex2f(8,10);
    glVertex2f(6,10);
    glEnd();

    glBegin(GL_QUADS);//RIGHT UP OBSTACLE
    glColor3f(1.0,1.0,1.0);
    glVertex2f(42,44);
    glVertex2f(44,44);
    glVertex2f(44,38);
    glVertex2f(42,38);
    glEnd();

    glBegin(GL_QUADS);//RIGHT DOWN OBSTACLE
    glColor3f(1.0,1.0,1.0);
    glVertex2f(42,16);
    glVertex2f(44,16);
    glVertex2f(44,10);
    glVertex2f(42,10);
    glEnd();

    glBegin(GL_QUADS);//UPPER BOUNDARY
    glColor3f(1.0,1.0,1.0);
    glVertex2f(0,50);
    glVertex2f(50,50);
    glVertex2f(50,48);
    glVertex2f(0,48);
    glEnd();

    glBegin(GL_QUADS);//BOTTOM BOUNDARY
    glColor3f(1.0,1.0,1.0);
    glVertex2f(0,0);
    glVertex2f(0,2);
    glVertex2f(50,2);
    glVertex2f(50,0);
    glEnd();

    glBegin(GL_QUADS);//LEFT BOUNDARY
    glColor3f(1.0,1.0,1.0);
    glVertex2f(0,0);
    glVertex2f(2,0);
    glVertex2f(2,50);
    glVertex2f(0,50);
    glEnd();

    glBegin(GL_QUADS);//RIGHT BOUNDARY
    glColor3f(1.0,1.0,1.0);
    glVertex2f(48,0);
    glVertex2f(50,0);
    glVertex2f(50,50);
    glVertex2f(48,50);
    glEnd();

    glBegin(GL_QUADS);//FOOD
    glColor3f(1.0,1.0,0.0);
    glVertex2f(a,b);
    glVertex2f(a+2,b);
    glVertex2f(a+2,b-2);
    glVertex2f(a,b-2);
    glEnd();

    glFlush();
}

void foodGen(){
    c = rand() % 20;
    a = food[c][0];
    b = food[c][1];

    glutPostRedisplay();
}


void prt(){
    char print[2];
    char str[] = "Your score is: ";

    itoa(score, print, 10);
    strcat(str, print);

    MessageBox(NULL, str, "Game Over", 0);
    exit(0);
}

void timer(int i){
    if(i  == 0){
        prt();
    } else if (i == 1){
        foodGen();
        glutTimerFunc(5000, timer, 1);
    }

}

void check(){
    for (int i = 0; i < 4 ; i += 1) {//bottom and up mid wall
        if (object [i][0] > 12 && object[i][0] < 36 && (object[i][1] == 19 || object[i][1] == 35)){//top and down
            prt();
        } else if ((object[1][0] == 13 || object[0][0] == 35 ) && (object[1][1] == 20 || object[1][1] == 36)){//left right
            prt();
        }
    }

    for (int j = 0; j < 4; j++) {//left up and down obstacle
        if (object[j][0] == 7 && ((object[j][1] > 38 && object[j][1] < 44) || (object[j][1] > 10 && object[j][1] < 16))){//left right
            prt();
        } else if ((object[0][0] == 6 && object[1][0] == 8) && (object[j][1] == 39 || object[j][1] == 43 || object[j][1] == 15 || object[j][1] == 11)){//top and down
            prt();
        }
    }

    for (int k = 0; k < 4; k++) {//right up and down obstacle
        if (object[k][0] == 43 && ((object[k][1] > 38 && object[k][1] < 44) || (object[k][1] > 10 && object[k][1] < 16))){//left right
            prt();
        } else if ((object[0][0] == 42 && object[1][0] == 44) && (object[k][1] == 39 || object[k][1] == 43 || object[k][1] == 15 || object[k][1] == 11)){//top and down
            prt();
        }
    }

    for (int l = 0; l < 4; l++) {//boundaries
        if (object[l][0] > 0 && object[l][0] < 50 && (object[l][1] == 49 || object[l][1] == 1)){//up and down
            prt();
        }else if ((object[l][0] == 1 || object[l][0] == 49) && object[l][1] > 0 && object[l][1] <50){//left and right
            prt();
        }
    }

    if (object[0][0] == a && object[0][1] == b){// food
        score++;
        foodGen();
        }
    }


void mySpecialfunc(int key, int x, int y){
    if(key == GLUT_KEY_DOWN){
        for (int i = 0; i < 4; i++) {
            object[i][1] -= 1;
        }
        } else if (key == GLUT_KEY_UP){
        for (int i = 0; i < 4; i++) {
            object[i][1] += 1;
        }
        } else if (key == GLUT_KEY_RIGHT){
        for (int i = 0; i < 4; i++) {
            object[i][0] += 1;
        }} else if (key == GLUT_KEY_LEFT){
        for (int i = 0; i < 4; ++i) {
            object[i][0] -= 1;
        }
    }
    glutPostRedisplay();
    check();
}

int main(int argc, char ** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(150,150);

    glutCreateWindow("Kashaf");
    glutSpecialFunc(mySpecialfunc);
    glutDisplayFunc(display);
    glutTimerFunc(20000, timer, 0);
    glutTimerFunc(0, timer, 1);
    init();
    glutMainLoop();

    return 0;
}