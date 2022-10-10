// Imagine++ project
// Project:  Panorama
// Author:   Pascal Monasse
// Date:     2013/10/08

#include <Imagine/Graphics.h>
#include <Imagine/Images.h>
#include <Imagine/LinAlg.h>
#include <vector>
#include <sstream>

using namespace Imagine;
using namespace std;

// Record clicks in two images, until right button click
void getClicks(Window w1, Window w2,
               vector<IntPoint2>& pts1, vector<IntPoint2>& pts2) {
    // ------------- TODO/A completer ----------
    int button;
    IntPoint2 p1,p2;
    int counter = 0;
    while(true){
        // We iterate between the 2 windows until the user makes a right click

        // The user must first click window1
        setActiveWindow(w1);
        button = getMouse(p1);
        drawString(p1.x(),p1.y(),to_string(counter),BLACK);
        fillCircle(p1,1,Color(255,0,0));
        if(button==3) break;
        // Then window2
        setActiveWindow(w2);
        button = getMouse(p2);
        drawString(p2.x(),p2.y(),to_string(counter),BLACK);
        fillCircle(p2,1,Color(255,0,0));
        if(button==3) break;

        // Once both points have been chosen they are added to the array
        // Points are illustrated in the images as red points to help the user
        // The number of the point is also illustrated
        counter ++;
        pts1.push_back(p1);
        pts2.push_back(p2);
    }


}

// Return homography compatible with point matches
Matrix<float> getHomography(const vector<IntPoint2>& pts1,
                            const vector<IntPoint2>& pts2) {
    size_t n = min(pts1.size(), pts2.size());
    if(n<4) {
        cout << "Not enough correspondences: " << n << endl;
        return Matrix<float>::Identity(3);
    }
    Matrix<double> A(2*n,8);
    Vector<double> B(2*n);
    // ------------- TODO/A completer ----------
    float xi,xi_prime,yi,yi_prime;
    int index = 0;
    // We build the linear system Ax = b
    for(unsigned int i = 0; i < 2*n; i++)
      {

        xi = pts1[index].x(); xi_prime = pts2[index].x();yi = pts1[index].y();yi_prime = pts2[index].y();
        index ++;

        // First line for the i-th pair
        A(i,0) = xi; A(i,1) = yi; A(i,2) = 1; A(i,3) = 0;
        A(i,4) = 0;A(i,5) = 0;A(i,6)= -xi_prime*xi; A(i,7) = -xi_prime*yi;
        B[i] = xi_prime;

        i++;
        // Second line for the i-th pair
        A(i,0) = 0; A(i,1) = 0; A(i,2) = 0; A(i,3) = xi;
        A(i,4) = yi;A(i,5) = 1;A(i,6)= -yi_prime*xi; A(i,7) = -yi_prime*yi;
        B[i] = yi_prime;
      }


    // Solving Ax = b, we store the result in B and load in H later
    B = linSolve(A, B);
    Matrix<float> H(3, 3);
    H(0,0)=B[0]; H(0,1)=B[1]; H(0,2)=B[2];
    H(1,0)=B[3]; H(1,1)=B[4]; H(1,2)=B[5];
    H(2,0)=B[6]; H(2,1)=B[7]; H(2,2)=1;

    // Sanity check
    for(size_t i=0; i<n; i++) {
        float v1[]={(float)pts1[i].x(), (float)pts1[i].y(), 1.0f};
        float v2[]={(float)pts2[i].x(), (float)pts2[i].y(), 1.0f};
        Vector<float> x1(v1,3);
        Vector<float> x2(v2,3);
        x1 = H*x1;
        cout << x1[1]*x2[2]-x1[2]*x2[1] << ' '
             << x1[2]*x2[0]-x1[0]*x2[2] << ' '
             << x1[0]*x2[1]-x1[1]*x2[0] << endl;
    }
    return H;
}

// Grow rectangle of corners (x0,y0) and (x1,y1) to include (x,y)
void growTo(float& x0, float& y0, float& x1, float& y1, float x, float y) {
    if(x<x0) x0=x;
    if(x>x1) x1=x;
    if(y<y0) y0=y;
    if(y>y1) y1=y;    
}

// Panorama construction
void panorama(const Image<Color,2>& I1, const Image<Color,2>& I2,
              Matrix<float> H) {
    Vector<float> v(3);
    float x0=0, y0=0, x1=I2.width(), y1=I2.height();

    v[0]=0; v[1]=0; v[2]=1;
    v=H*v; v/=v[2];
    growTo(x0, y0, x1, y1, v[0], v[1]);

    v[0]=I1.width(); v[1]=0; v[2]=1;
    v=H*v; v/=v[2];
    growTo(x0, y0, x1, y1, v[0], v[1]);

    v[0]=I1.width(); v[1]=I1.height(); v[2]=1;
    v=H*v; v/=v[2];
    growTo(x0, y0, x1, y1, v[0], v[1]);

    v[0]=0; v[1]=I1.height(); v[2]=1;
    v=H*v; v/=v[2];
    growTo(x0, y0, x1, y1, v[0], v[1]);

    cout << "x0 x1 y0 y1=" << x0 << ' ' << x1 << ' ' << y0 << ' ' << y1<<endl;

    Image<Color> I(int(x1-x0), int(y1-y0));
    setActiveWindow( openWindow(I.width(), I.height()) );
    I.fill(BLACK);
    // ------------- TODO/A completer ----------
    Matrix<float> H_inv(3, 3);
    H_inv = inverse(H);

    Vector<float> new_pixel(3);
    int new_w;
    int new_h;
    bool in_I1,in_I2;
    for(int w=x0;w<I.width();w++){
        for(int h=y0;h<I.height();h++){
            //Image 2
            in_I2 = (0<= w and w <I2.width() and 0<=h and h<I2.height());
            if(in_I2) I(w-x0,h-y0) = I2(w,h);
            // Pulling pixels to image 1 and getting the intensity values
            new_pixel[0] = w; new_pixel[1] = h; new_pixel[2] = 1;
            new_pixel = H_inv * new_pixel;
            new_pixel /= new_pixel[2];

            new_w = int(new_pixel[0]); new_h = int(new_pixel[1]);
            in_I1 = (0<=new_w and new_w <I1.width() and 0<=new_h and new_h<I1.height());
            if(in_I1){
                if (in_I2){// Averaging if in I1 and I2
                    // We add component by component, this avoids overflow
                    // Arithmetic Mean
                    I(w-x0,h-y0).r() = I1(new_w,new_h).r()*0.5 + I2(w,h).r()*0.5;
                    I(w-x0,h-y0).g() = I1(new_w,new_h).g()*0.5 + I2(w,h).g()*0.5;
                    I(w-x0,h-y0).b() = I1(new_w,new_h).b()*0.5 + I2(w,h).b()*0.5;
                    // Experimenting with Geometric Mean
//                    I(w-x0,h-y0).r() = sqrt(I1(new_w,new_h).r() *I2(w,h).r());
//                    I(w-x0,h-y0).g() = sqrt(I1(new_w,new_h).g() *I2(w,h).g());
//                    I(w-x0,h-y0).b() = sqrt(I1(new_w,new_h).b() *I2(w,h).b());
                }
                else{
                   I(w-x0,h-y0) = I1(new_w,new_h);
                }

            }
        }
    }

    display(I,0,0);
}

// Main function
int main(int argc, char* argv[]) {
    const char* s1 = argc>1? argv[1]: srcPath("image0006.jpg");
    const char* s2 = argc>2? argv[2]: srcPath("image0007.jpg");
//    const char* s1 = argc>1? argv[1]: srcPath("ex_tmp.jpg");
//    const char* s2 = argc>2? argv[2]: srcPath("ex3.jpg");

    // Load and display images
    Image<Color> I1, I2;
    if( ! load(I1, s1) ||
        ! load(I2, s2) ) {
        cerr<< "Unable to load the images" << endl;
        return 1;
    }
    Window w1 = openWindow(I1.width(), I1.height(), s1);
    display(I1,0,0);
    Window w2 = openWindow(I2.width(), I2.height(), s2);
    setActiveWindow(w2);
    display(I2,0,0);

    // Get user's clicks in images
    vector<IntPoint2> pts1, pts2;
    getClicks(w1, w2, pts1, pts2);

    vector<IntPoint2>::const_iterator it;
    cout << "pts1="<<endl;
    for(it=pts1.begin(); it != pts1.end(); it++)
        cout << *it << endl;
    cout << "pts2="<<endl;
    for(it=pts2.begin(); it != pts2.end(); it++)
        cout << *it << endl;

    // Compute homography
    Matrix<float> H = getHomography(pts1, pts2);
    cout << "H=" << H/H(2,2);

    // Apply homography
    panorama(I1, I2, H);

    endGraphics();
    return 0;
}
