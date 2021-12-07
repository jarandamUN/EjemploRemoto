#include "md-simul.h"
#include <cmath>

void initial_conditions(Particle & body)
{
  body.Ry = 1.6598;
  body.Vx = 0.23698;

  body.rad = 0.235;
  body.mass = 0.29698;

}

void compute_force(Particle & body)
{
  // reset force
  body.Fx = body.Fy = body.Fz = 0.0;
  body.E = body.Eu = body.Ep = body.Ec = 0.0;                                //Reseteo de las energias, donde: E => Diferencia de energia relativa
                                                                             //   Ec => Energia cinética          Ep => Energia potencial gravitacional
                                                                             //   Eu => Energia potencial asociada a la interacción con las paredes
  double E0 = -0.29698*1.6598*G + 0.29698*0.23698*0.23698/2;                 //Energia inicial, de la forma: mgh_0 + (m(v_0)'2)/2 
  body.Ec = body.mass*body.Vx*body.Vx/2 + body.mass*body.Vy*body.Vy/2;       //Ec = (m(V_x)´2)/2 + (m(V_y)´2)/2
  body.Ep = -body.mass*body.Ry*G;                                            //Ep = mgh

  // gravitational force
  body.Fy += body.mass*G;

  // force with ground
  double delta = body.rad - body.Ry;
  if (delta > 0) {
    body.Fy += K*delta;
    body.Eu += K*delta*delta/2;                                              //Eu = (Kd'2)/2
    //body.Fy -= 1.9876*body.Vy; 
  }

  delta = body.Rx + body.rad - LR;
  if(delta > 0){
    body.Fx -= K*delta;
    body.Eu += K*delta*delta/2;                                              //Eu = (Kd'2)/2
  }

  delta = LL - body.Rx + body.rad;
  if(delta > 0){
    body.Fx += K*delta;
    body.Eu += K*delta*delta/2;                                              //Eu = (Kd'2)/2
  } 

  body.E = std::fabs(body.Ec + body.Ep + body.Eu - E0)/ E0;                  //E (recordar que es la dif. de energia relativa), siguiendo la formula del profe
                                                                             
  }


void print(Particle & body, double time)
{
  std::cout << time << "  " 
	    << body.Rx << "  "
	    << body.Ry << "  "
	    << body.Rz << "  "
	    << body.Vx << "  "
	    << body.Vy << "  "
	    << body.Vz << "  "
      << body.Ec << "  "                                                     // Impresión de valores Ec, Ep, Eu, E,  con respectiva columna:
      << body.Ep << "  "                                                     // Columnas:             8,  9, 10, 11
      << body.Eu << "  " 
      << body.E << "  "
	    << "\n";
}
