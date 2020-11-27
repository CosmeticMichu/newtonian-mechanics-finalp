#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

typedef std::vector<double> length; 

int N = 5; //numero de datos que fueron tomados
//se declaran los vectores que van a guardar las mediciones
length s1(N, 0.0);
length s2(N, 0.0);
length s3(N, 0.0);
length s4(N, 0.0);
length h1(N, 0.0);
length h2(N, 0.0);
length h3(N, 0.0);
length h4(N, 0.0);

double average (length);
double uncertainty (double);
double angle (double s, double h);
double angle_unty (double s, double ds, double h, double dh);

int main(int argc, char **argv)
{
    //falta fijar la precision de cout
    double avs1 = 0.0, avs2 = 0.0, avs3 = 0.0, avs4 = 0.0, avh1 = 0.0, avh2 = 0.0, avh3 = 0.0, avh4 = 0.0; //se crean vectores de datos high (s) y shadow (s)
    double angle1 = 0.0; //se crean variables para guardar angulos formados por la altura del objeto y su sombra
    double dangle1 = 0.0; //variables para guardar la incertidumbre en la medicion del angulo
    double dB_A = 1, dB_Az = 1, dB_C = 1, dA_Az = 1, dA_C = 1, dC_Az = 1; //variables para la distancia (N-S) que separa las distintas ciudades

    const double delta = std::atof(argv[1]); //lee incertidumbre de medicion de s y h desde la terminal
    double deltaf = 0.0; //variable para guardar incertidumbre total cuando se promedien s y h

    std::cout << "Los valores ingresados fueron: " << "\n";
    std::cout << "s1" << "\t" << "h1" << "\t" << "s2" << "\t" << "h2" << "\t" << "s3" << "\t" << "h3" << "\t" << "s4" << "\t" << "h4" << "\n"; //imprime en consola los datos ingresados para poder verificar
    std::ifstream fin ("input.txt");
    
    fin.precision(4); //esta precision depende de como se mida
    fin.ignore(8*N,'#'); //esta linea es para organizar el .txt e ingresar los datos mas facilmente
    
    for(int ii = 0; ii <= N-1; ++ii) //ingresa los datos en el .txt al vectores en el programa
    {
        fin >> s1[ii]; //como fstream barre por filas, se deja que se haga el barrido por filas y cada vez se ingresa cada valor en un vector distinto, con esto se simula que lee
        std::cout << s1[ii] << "\t"; //por columnas, la estrucutra por colummnas en el txt es mas facil de leer para nosotros
        fin >> h1[ii];
        std::cout << h1[ii] << "\t";
        fin >> s2[ii];
        std::cout << s2[ii] << "\t";
        fin >> h2[ii];
        std::cout << h2[ii] << "\t";
        fin >> s3[ii];
        std::cout << s3[ii] << "\t";
        fin >> h3[ii];
        std::cout << h3[ii] << "\t";
        fin >> s4[ii];
        std::cout << s4[ii] << "\t";
        fin >> h4[ii];
        std::cout << h4[ii] << "\n";
    }
    
    fin.close();

    deltaf = uncertainty(delta); //calcula la incertidumbre total despues de hacer el promedio

    //se calculan los promedios para cada conjunto de datos
    avs1 = average(s1);
    avh1 = average(h1);
    avs2 = average(s2);
    avh2 = average(h2);
    avs3 = average(s3);
    avh3 = average(h3);
    avs4 = average(s4);
    avh4 = average(h4);

    //se calcula aproximadamente el angulo de incidencia de la luz solar el dia y la hora de la medicion en cada lugar
    angle1 = angle(avs1,avh1);
    dangle1 = angle_unty(avs1,deltaf,avh1,deltaf);
    std::cout << angle1 << " +/- " << dangle1  << "\n";

    return 0;
}

//funcion de promedios
double average(length l)
{
    double sum = 0.0;
    for (auto &val : l){
        sum += val;
    }

    return sum/l.size();
}

//funcion de expansion de incertidumbre segun el error de medicion
double uncertainty (double ucty)
{
    return N*ucty;
}

//calcula el angulo de incidencia en funcion de la altura de un objeto y el largo de su sombra
double angle (double s, double h)
{
    double rad;
    rad = atan(s/h);
    return (rad*180.0)/M_PI;
}
//calcula la incertidumbre segun el calculo del angulo de incidencia
double angle_unty (double s, double ds, double h, double dh)
{
    return (sqrt((h*ds)*(h*ds)+(s*dh)*(s*dh)))/(s*s+h*h);
}
