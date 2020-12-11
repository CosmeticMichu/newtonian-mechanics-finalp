#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

typedef std::vector<double> length; 

double average(length l);
double uncertainty (length data, double ucty);
double angle (length s, length h);
double angle_unty (length s, length h, double ucty);
double radius (double dist, double phi1, double phi2);
double radius_unty (double d, double phi1, double phi2, double dphi1, double dphi2);
double gravity (length L, length T);
double gravity_ucty (length l, length T, double ucty, double uctyT);
double var(length data);
double mass(double r, double g);
double mass_ucty(double r, double dr, double g, double dg);
//double rad_to_deg (double rad); //por si se necesita imprimir valores en grados

int main(int argc, char **argv)
{
	//declaraciones
	
	double angle1 = 0.0, angle2 = 0.0, angle3 = 0.0, angle4 = 0.0; //se crean variables para guardar angulos formados por la altura del objeto y su sombra
	double dangle1 = 0.0, dangle2 = 0.0, dangle3 = 0.0, dangle4 = 0.0; //variables para guardar la incertidumbre en la medicion del angulo
	double dB_A = 137470, dB_Az = 212270, dB_C = 90590, dA_Az = 348050, dA_C = 46900, dC_Az = 302000; //variables para la distancia (N-S) que separa las distintas ciudades
	double rB_A = 0.0, rB_Az = 0.0, rB_C = 0.0, rA_Az = 0.0, rA_C = 0.0, rC_Az = 0.0; //variables para el radio segun los valores medidos en cada ciudad
    double drB_A = 0.0, drB_Az = 0.0, drB_C = 0.0, drA_Az = 0.0, drA_C = 0.0, drC_Az = 0.0; //variables para incertidumbre en el radio
	const double delta = std::atof(argv[1]); //lee incertidumbre de medicion de s y h desde la terminal
	const double deltal = std::atof(argv[2]); //lee la incertidumbre de medicion de l desde la terminal
	const double deltaT = std::atof(argv[3]); //lee la incertidumbre de medicion de T desde la terminal

	double gA = 0.0, gAz = 0.0, gB = 0.0, gC = 0.0; //variables para guardar el valor de la gravedad en cada ciudad
	double dgA = 0.0, dgAz = 0.0, dgB = 0.0, dgC = 0.0;//variables para la incertidumbre de la medidicion de la gravedad en cada ciudad
 
	double gf = 0.0; //variable para guardar el valor promedio de la gravedad
	double dgf = 0.0; //variable para guardar la incertidumbre del valor promedio de la gravedad

	double rf = 0.0; //guarda el radio de la tierra segun las mediciones en distintas ciudades
    double drf = 0.0; //guarda la inertidumbre de medicion del radio de la tierra entre las zonas medidas

	double rfc = 0.0; //guarda el radio corregido de la tierra segun las mediciones en distintas ciudades
    double drfc = 0.0; //guarda la inertidumbre de medicion del radio corregido de la tierra entre las zonas medida
	
	double M = 0.0; //estos valores guardaran finalmente los valores de masa para la tierra y su respectiva incertidumbre
	double dM = 0.0;
	
	//numero de datos que fueron tomados para s, h y l
	const int N = 5;
	
	//numero de datos tomados para el periodo T
	
	const int NT = 10;
	
    //se declaran los vectores que van a guardar las mediciones
    length s1(N, 0.0);
    length s2(N, 0.0);
    length s3(N, 0.0);
    length s4(N, 0.0);
    length h1(N, 0.0);
    length h2(N, 0.0);
    length h3(N, 0.0);
    length h4(N, 0.0);
	
	//vectores para promediar los valores del radio
	length avgr(6, 0.0); //el 6 es porque usamos valores cruzados de radio, es decir, tendremos 4 (ciudades en las que medimos) combinado (es lo mismo radio según Ayapel y Aguazul que Aguazul y Ayapel) 2 (agrupamos por parejas) valores para el radio
    length avgdr(6, 0.0); //incertidumbre para el radio

	length avgrc(3, 0.0); //el 3 es porque de los 6 iniciales, solo 3 sirvieron
    length avgdrc(3, 0.0); //incertidumbre para el radio corregido


	//pendulo

	//vectores para datos de L
	length l1(N, 0.0);
    length l2(N, 0.0);
	length l3(N, 0.0);
	length l4(N, 0.0);
	
	//vectores para datos de T
	
	length T1(NT, 0.0);
    length T2(NT, 0.0);
	length T3(NT, 0.0);
	length T4(NT, 0.0);
	
	//vectores para promediar los valores de la gravedad
	length avgg(4, 0.0); //4 porque tomados 4 conjuntos de datos para, con cada uno, calcular la gravedad
    length avgdg(4, 0.0);
	
	// carga de datos e impresion de los mismos en consola

	std::cout << "Los valores ingresados fueron: " << "\n";
    std::cout << "s1(A)" << "\t" << "h1(A)" << "\t" << "l1(A)" << "\t" << "s2(Az)" << "\t" << "h2(Az)" << "\t" << "l2(Az)" << "\t" << "s3(B)" << "\t" << "h3(B)" << "\t" << "l3(B)" << "\t" << "s4(C)" << "\t" << "h4(C)" << "\t" << "l4(C)" << "\n"; //imprime en consola los datos ingresados para poder verificar    std::ifstream fin ("input.txt");

    std::ifstream fin ("input.txt");
    
    fin.precision(5); //esta precision depende de como se mida
    fin.ignore(1000,'#'); //esta linea es para organizar el .txt e ingresar los datos mas facilmente
    
    for(int ii = 0; ii <= N-1; ++ii) //ingresa los datos en el .txt al vectores en el programa
    {
        fin >> s1[ii]; //como fstream barre por filas, se deja que se haga el barrido por filas y cada vez se ingresa cada valor en un vector distinto, con esto se simula que lee
        std::cout << s1[ii] << "\t"; //por columnas, la estrucutra por colummnas en el txt es mas facil de leer para nosotros
        fin >> h1[ii];
        std::cout << h1[ii] << "\t";
        fin >> l1[ii];
        std::cout << l1[ii] << "\t";
		fin >> s2[ii];
        std::cout << s2[ii] << "\t";
        fin >> h2[ii];
        std::cout << h2[ii] << "\t";
        fin >> l2[ii];
        std::cout << l2[ii] << "\t";
		fin >> s3[ii];
        std::cout << s3[ii] << "\t";
        fin >> h3[ii];
        std::cout << h3[ii] << "\t";
        fin >> l3[ii];
        std::cout << l3[ii] << "\t";
		fin >> s4[ii];
        std::cout << s4[ii] << "\t";
        fin >> h4[ii];
        std::cout << h4[ii] << "\t";
		fin >> l4[ii];
        std::cout << l4[ii] << "\n";
	}
    
    fin.close();

	std::cout << "\n" << "Para las longitudes, y " << "\n";
	std::cout << "\n" << "T1(A)" << "\t" << "T2(Az)" << "\t" << "T3(B)" << "\t" << "T4(C)" << "\n"; //imprime en consola los datos ingresados para poder verificar std::ifstream finT ("input2.txt");

	
	std::ifstream finT ("input2.txt"); //lee los datos para el periodo de oscilacion
    
    finT.precision(5); //esta precision depende de como se mida
    finT.ignore(1000,'#'); //esta linea es para organizar el .txt e ingresar los datos mas facilmente, ognora hasta 1000 datos o lo que este antes de #
    
    for(int ii = 0; ii <= NT-1; ++ii) //ingresa los datos en el .txt al vectores en el programa
    {
        finT >> T1[ii]; //como fstream barre por filas, se deja que se haga el barrido por filas y cada vez se ingresa cada valor en un vector distinto, con esto se simula que lee
        std::cout << T1[ii] << "\t"; //por columnas, la estrucutra por colummnas en el txt es mas facil de leer para nosotros
        finT >> T2[ii];
        std::cout << T2[ii] << "\t";
        finT >> T3[ii];
        std::cout << T3[ii] << "\t";
		finT >> T4[ii];
        std::cout << T4[ii] << "\n";
	}
    
    finT.close();
	
	std::cout << "\n" << "Para los periodos de oscilacion" << std::endl;
	
	//calculos
	
	angle1 = angle(s1,h1);
	angle2 = angle(s2,h2);
	angle3 = angle(s3,h3);
	angle4 = angle(s4,h4);
	
	dangle1 = angle_unty(s1, h1, delta);
    dangle2 = angle_unty(s2, h2, delta);
    dangle3 = angle_unty(s3, h3, delta);
    dangle4 = angle_unty(s4, h4, delta);

    std::cout << "\n"  << "angAyapel: " << angle1*180/M_PI << " +/- " << dangle1*180/M_PI << "\n";
    std::cout << "angAguazul: " << angle2*180/M_PI << " +/- " << dangle2*180/M_PI << "\n";
    std::cout << "angBarrancabermeja: " << angle3*180/M_PI << " +/- " << dangle3*180/M_PI << "\n";
    std::cout << "angCucuta: " << angle4*180/M_PI << " +/- " << dangle4*180/M_PI << "\n";

	rB_A = radius(dB_A,angle3,angle1);
    drB_A = radius_unty(dB_A,angle3,angle1,dangle3,dangle1);
    rB_Az = radius(dB_Az,angle3, angle2);
    drB_Az = radius_unty(dB_Az,angle3,angle2,dangle3,dangle2);
    rB_C = radius(dB_C,angle3, angle4);
    drB_C = radius_unty(dB_C,angle3,angle4,dangle3,dangle4);
    rA_Az = radius(dA_Az,angle1, angle2);
    drA_Az = radius_unty(dA_Az,angle1,angle2,dangle1,dangle2);
    rA_C = radius(dA_C,angle1, angle4);
    drA_C = radius_unty(dA_C,angle1,angle4,dangle1,dangle4);
    rC_Az = radius(dC_Az,angle4, angle2);
    drC_Az = radius_unty(dC_Az,angle4,angle2,dangle4,dangle2);
	
    std::ofstream fout ("radius.txt");
    
	fout << "Radio medido entre Barrancabermeja y Ayapel: " << rB_A << " +/- " << drB_A << " metros" << "\n";
	fout << "Radio medido entre Barrancabermeja y Aguazul: " << rB_Az << " +/- " << drB_Az << " metros" << "\n";
	fout << "Radio medido entre Barrancabermeja y Cucuta: " << rB_C << " +/- " << drB_C << " metros" << "\n";
	fout << "Radio medido entre Ayapel y Aguazul: " << rA_Az << " +/- " << drA_Az << " metros" << "\n";
	fout << "Radio medido entre Ayapel y Cucuta: " << rA_C << " +/- " << drA_C << " metros" << "\n";
	fout << "Radio medido entre Cucuta y Aguazul: " << rC_Az << " +/- " << drC_Az << " metros" << "\n";

    fout.close();
    
	avgr[0]=rB_A, avgr[1]=rB_Az, avgr[2]=rB_C, avgr[3]=rA_Az, avgr[4]=rA_C, avgr[5]=rC_Az;
    avgdr[0]=drB_A, avgdr[1]=drB_Az, avgdr[2]=drB_C, avgdr[3]=drA_Az, avgdr[4]=drA_C, avgdr[5]=drC_Az;
	
	
	avgrc[0]=rB_A, avgrc[1]=rB_C, avgrc[2]=rC_Az;
    avgdrc[0]=drB_A, avgdrc[1]=drB_C, avgdrc[2]=drC_Az;
	
	rf=average(avgr);
    drf=average(avgdr);

	rfc=average(avgrc);
    drfc=average(avgdrc);

    std::cout << "\n" << "El radio terrestre, segun las medidas tomadas, es: "  << rf << " +/- " << drf << " metros" << "\n";
	std::cout << "\n" << "El radio terrestre corregido, segun las medidas tomadas, es: "  << rfc << " +/- " << drfc << " metros" << "\n";
	
	gA = gravity(l1, T1);
	gAz = gravity(l2, T2);
	gB = gravity(l3, T3);
	gC = gravity(l4, T4);

	dgA = gravity_ucty(l1,T1,deltal,deltaT);
	dgAz = gravity_ucty(l2,T2,deltal,deltaT);
	dgB = gravity_ucty(l3,T3,deltal,deltaT);
	dgC = gravity_ucty(l4,T4,deltal,deltaT);
	
	std::cout << "\n" << "El valor de gravedad medido en Ayapel - Cordoda, fue : " << gA << " +/- " << dgA << "\n";
	std::cout << "El valor de gravedad medido en Aguazul - Casanare, fue : " << gAz << " +/- " << dgAz << "\n";
	std::cout << "El valor de gravedad medido en Barrancabermeja - Santander, fue : " << gB << " +/- " << dgB << "\n";
	std::cout << "El valor de gravedad medido en Cucuta - Norte de Santander, fue : " << gC << " +/- " << dgC << "\n";

	avgg[0]=gA, avgg[1]=gAz, avgg[2]=gB, avgg[3]=gC;
    //avgdg[0]=dgA, avgdg[1]=dgAz, avgdg[2]=dgB, avgdg[3]=dgC;

	gf = average(avgg);
	dgf = var(avgg);
	
	std::cout << "\n" << "El valor promedio para la gravedad es: " << gf << " +/- " << dgf << "\n";
	
	M = mass(rfc,gf);
	dM = mass_ucty(rfc,drfc,gf,dgf);
	
	std::cout << "\n" << "El valor estimado para la masa de la tierra es: " << M << " +/- " << dM << std::endl;
	
	return 0;
}

double average(length l)
{
    double n = l.size();
	double sum = 0.0;
    for (auto &val : l){
        sum += val;
    }

    return sum/n;
}

double var(length data)
{
	double var = 0.0;
	double sum = 0.0;
	double n = data.size();
	
	for(auto &val : data){
		sum += (val-average(data))*(val-average(data)); 
	}
	var = sum/(n-1.0);
	
	return var;
}

double uncertainty (length data, double ucty)
{
	double vr = 0.0;
	vr = var(data);
    return sqrt(vr+ucty*ucty);
}

double angle (length s, length h)
{
	double high = 0.0;
	double shadow = 0.0;
	
	high = average(h);
	shadow = average(s);
	
    double rad = 0.0;
    rad = atan((M_PI/2.0)-(shadow/high));
    return rad;
}

/*double rad_to_deg (double rad)
{
	return (rad*180.0)/M_PI
}*/

double angle_unty (length s, length h, double ucty)
{
	double S = 0.0;
	double dS = 0.0;
	double H = 0.0;
	double dH = 0.0;
	
	S = average(s);
	dS = uncertainty(s,ucty);
	H = average(h);
	dH = uncertainty(h,ucty);
	
    return (sqrt((H*dS)*(H*dS)+(S*dH)*(S*dH)))/(S*S+H*H);
}

double radius (double dist, double phi1, double phi2)
{
    return dist/std::abs(phi1-phi2);
}

double radius_unty (double d, double phi1, double phi2, double dphi1, double dphi2)
{
	return sqrt((d*d)/(pow(phi2-phi1,4))*(dphi1*dphi1+dphi2*dphi2)); //hay que ver que esto no bote problemas, porque pow trabaja con floats y le estoy metiendo doubles
}

double gravity (length L, length T)
{
	double l = 0.0;
	double t = 0.0;
	
	l = average(L);
	t = average(T);
	
	return 4.0*M_PI*M_PI*((l)/(t*t));
}

double gravity_ucty (length l, length T, double ucty, double uctyT)
{
	double L = 0.0;
	double dL = 0.0;
	double t = 0.0;
	double dt = 0.0;
	
	L = average(l);
	dL = uncertainty(l, ucty);
	t = average(T);
	dt = uncertainty(T, uctyT);
	return ((4.0*M_PI*M_PI)/(t))*sqrt(dL*dL+(((2*L)/(t))*((2*L)/(t)))*(dt)*(dt));
}

double mass(double r, double g)
{
	double G = 6.674*std::pow(10,-11);
	return (1.0/G)*(g*r*r);
}

double mass_ucty(double r, double dr, double g, double dg)
{
	double G = 6.674*std::pow(10,-11);
	return ((r*r)/(G))*sqrt(dg*dg+((2.0*g)/(r))*((2.0*g)/(r))*dr*dr);
}
