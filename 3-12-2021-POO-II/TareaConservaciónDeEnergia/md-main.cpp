#include "md-simul.h" // this has all functions declarations

int main(void)
{
  Particle ball;

  // start system
  initial_conditions(ball);
  compute_force(ball);
  start_integration(ball, DT);
  print(ball, 0.0);

  // evolve
  for(int istep = 0; istep < 20/DT; ++istep) {              //se modificó la condición del ciclo de istep < NSTEPS por 20/DT, para sin necesidad de cambiar
    time_integration(ball, DT);                             //  NSTEPS en md-simul.h, se cumpla la condición en la que el tiempo total sea de 20 segundos
    compute_force(ball);                                    //  aún cuando se cambie el DT.
    print(ball, istep*DT);
  }
  
  return 0;                                                 //- Comandos usados para ver resultados:
}                                                           //  g++ md-main.cpp md-simul-energy.cpp integrator-leapfrog.cpp -o leapfrog.x 
                                                            //  ./leapfrog.x > datos-leapfrog.txt

                                                            //- Para graficarla:
                                                            //  gnuplot
                                                            //  > Dentro de gnuplot:
                                                            //    plot 'datos-leapfrog.txt' u 1:11 w lp t 'Diferencia relativa de energia dado Dt = 1.0'
                                                            //    set xlabel 'Tiempo'
                                                            //    set ylabel 'Dif. relativa de energia'
                                                            //    set logscale y                                                (Para visualizarlos mejor)
                                                            //    replot 

