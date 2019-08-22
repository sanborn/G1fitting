
#include "Clothoid.hh"
#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>

Clothoid::valueType m_pi = 3.14159265358979323846264338328 ;

using namespace std ;

int
main(int argc, char** argv) {
  cout.precision(15);
  if ( argc < 8) {
    cout << "Required arguments: x0 y0 angle0 x1 y1 angle1 pointCount" << "\n";
    return 1;
  }
  double x0, y0, angle0, x1, y1, angle1;
  int npts;
  std::ofstream fileOutput;
  x0 = atof(argv[1]);
  y0 = atof(argv[2]);
  angle0 = atof(argv[3]);
  x1 = atof(argv[4]);
  y1 = atof(argv[5]);
  angle1 = atof(argv[6]);
  npts = atoi(argv[7]);

  double p0 [2];
  double p1 [2];
  p0[0] = x0;
  p0[1] = y0;
  p1[0] = x1;
  p1[1] = y1;

  Clothoid::ClothoidCurve curve = Clothoid::ClothoidCurve(p0, m_pi*angle0, p1, m_pi*angle1);
  double k = curve.getKappa();
  double dk = curve.getKappa_D();
  double len = curve.getSmax();
  double interval = len/(npts - 1);
  // file output will be a json array
  cout << "[";
  for (int i = 0; i < npts; i++) {
    double t = i * interval;
    double intC = 0.0;
    double intS = 0.0;
    Clothoid::GeneralizedFresnelCS(dk * pow(t, 2.0), k*t, angle0, intC, intS);
    double x = x0 + t * intC;
    double y = y0 + t * intS;
    double pointK = k + dk*t;
    cout << "{\"index\": "<<i<<", \"coordinate\": ["<<x<<", "<<y<<"], \"curvature\": "<<pointK<<"}";
    if (i == npts - 1) {
      cout << "]\n";
    } else {
      cout << ",\n";
    }
  }
  return 0;
}
