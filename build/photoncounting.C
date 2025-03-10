void photoncounting()
{
//Drawing QE Graph ------------------------------------------------

double x[72] = {5, 5, 4.76 , 4.71 , 4.66 , 4.6 , 4.55 , 4.51 , 4.46 , 4.41 , 4.37 , 4.3 , 4.23 , 4.17 , 4.05 , 3.92 , 3.76 , 3.62 , 3.47 , 3.34 , 3.24 , 3.13 , 3.03 , 2.92 , 2.83 , 2.74 , 2.67 , 2.6 , 2.53 , 2.47 , 2.41 , 2.37 , 2.34 , 2.31 , 2.29 , 2.27 , 2.23 , 2.21 , 2.18 , 2.14 , 2.11 , 2.08 , 2.06 , 2.04 , 2.02 , 2.01 , 1.99 , 1.98 , 1.97 , 1.96 , 1.95 , 1.94 , 1.93 , 1.92 , 1.9 , 1.9 , 1.88 , 1.87 , 1.87 , 1.86 , 1.85 , 1.84 , 1.83 , 1.83 , 1.82 , 1.81 , 1.8 , 1.79 , 1.79 , 1.78 , 1.77, 1.77
};
double y[72] = {0, 0, 2.08 , 2.48 , 2.95 , 3.51 , 4.25 , 5.15 , 6.35 , 7.7 , 9.33 , 11.1 , 13.22 , 15.47 , 18.1 , 20.45 , 22.7 , 24.34 , 25.65 , 26.1 , 26.1 , 25.65 , 25.21 , 24.34 , 23.51 , 21.92 , 19.74 , 18.1 , 16.58 , 15.47 , 13.69 , 12.33 , 10.72 , 9.33 , 8.25 , 6.93 , 6.03 , 5.34 , 4.56 , 3.97 , 3.39 , 2.9 , 2.52 , 2.19 , 1.84 , 1.57 , 1.35 , 1.15 , 0.98 , 0.87 , 0.77 , 0.67 , 0.59 , 0.51 , 0.43 , 0.36 , 0.31 , 0.26 , 0.22 , 0.18 , 0.15 , 0.13 , 0.11 , 0.09 , 0.07 , 0.06 , 0.05 , 0.04 , 0.04 , 0.03 , 0, 0
};

double cos[19] = {1, 0.996, 0.983, 0.966, 0.939, 0.908, 0.867, 0.82, 0.766, 0.711, 0.646, 0.572, 0.502, 0.434, 0.358, 0.269, 0.183, 0.101, 0.013};
double refl[19] = {0.832, 0.8197, 0.8176, 0.8197, 0.8176, 0.8176, 0.8094, 0.7992, 0.7848, 0.7418, 0.709, 0.6578, 0.6168, 0.5225, 0.4365, 0.334, 0.2049, 0.0881, 0.0246};
double reee[19] = {1.0, 1.0, 1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0};

TGraph *gr = new TGraph(72, x, y);

TGraph *angle = new TGraph(19, cos, refl);

gr -> SetTitle("Quantum Efficiency;Energy (eV);QE (%)");
gr -> SetMarkerStyle(8);
gr -> SetMarkerSize(1);
gr -> SetMarkerColor(kBlack);

angle -> SetTitle("Angular Response;cos #theta;Angular Response");
angle -> SetMarkerStyle(8);
angle -> SetMarkerSize(1);
angle -> SetMarkerColor(kBlack);

//Splining -------------------------------------------------------------

auto smooth = new TGraphSmooth("normal");
TGraph *sm = smooth -> SmoothKern(gr, "normal");
TGraph *sm_2 = smooth -> SmoothKern(angle, "normal");

//Quintic spline after graph smoothing gives the best result.

auto spline = new TSpline5("spline", gr);
spline -> SetLineColor(kRed);
spline -> SetLineWidth(2);

auto splineang = new TSpline5("splineang", angle);
splineang -> SetLineColor(kRed);
splineang -> SetLineWidth(2);

/*
TCanvas *c1 = new TCanvas();
c1 -> Divide(2,1);
c1 -> cd(1);
gr -> Draw("AP");
spline -> Draw("same");
c1 -> cd(2);
angle -> Draw("AP");
splineang -> Draw("same");
*/
/*
auto legend = new TLegend(0.7,0.8,0.9,0.9);
legend -> AddEntry(angle, "Reflectivity", "lp");
legend -> AddEntry(splineang, "Spline Curve", "lp");
legend -> Draw();   */

//Calculating Valid Entry Numbers ----------------------------------------

fstream table;
table.open("numbers_nt_Eid.csv", ios::in);
std::vector<int> t_ms;
std::string list;
while (std::getline(table, list))
{
    std::stringstream sts(list);
    int value;
    if (sts >> value)
    {
        t_ms.push_back(value);
    }
}
table.close();
int esize = 1000 - t_ms.size();

//Reading Geant4 Results --------------------------------------------

std::vector<std::tuple<double, int, double>> comb;
std::vector<double> refer;

fstream file;
file.open("numbers_nt_num.csv", ios::in);
std::string line;
while (std::getline(file, line))
{
    std::stringstream sts(line);
    std::string a, b, c;
    if (std::getline(sts, a, ',') && std::getline(sts, b, ',') && std::getline(sts, c, ','))
    {
        double firstValue = std::stod(a);
        int secondValue = std::stoi(b);
        double thirdValue = std::stod(c);
        std::tuple<double,int,double> tuple = std::make_tuple(firstValue,secondValue, thirdValue);
        comb.push_back(tuple);
        refer.push_back(firstValue);
    }
}
file.close();

std::vector<double> Energy, Angle;

for (const auto& c_m : comb)
{
    double E = std::get<0>(c_m);
    double theta = std::get<2>(c_m);
    if (std::find(t_ms.begin(), t_ms.end(), std::get<1>(c_m)) == t_ms.end()) 
    {
        Energy.push_back(E);
        Angle.push_back(theta);
    }
}

//Applying Angle-dependent Reflectivity-----------------------------------------

std::vector<double> x_ms;

for (double Angle_m : Angle)
{
    double x_m = splineang -> Eval(Angle_m);
    x_ms.push_back(x_m);
    
}

//Finding Photon Number with QE Applied -----------------------------------------

std::vector<double> y_ms;

for (double Energy_m : Energy)
{
    double y_m = spline -> Eval(Energy_m);
    if (0 <= y_m && y_m <= 26.1)
    {
        y_ms.push_back(y_m);
    }
    else y_ms.push_back(0.0);
    
}
double sum = std::inner_product(x_ms.begin(), x_ms.end(), y_ms.begin(), 0);
double per = sum / x_ms.size();
int refsize = refer.size();
std::cout << "1. photon number with QE & angular dependence = " << round(10 * sum / esize) / 1000 << std::endl;
std::cout << "2. photon number with nothing applied = " << x_ms.size() / esize << std::endl;
std::cout << "3. ratio between 1 & 2 = " << per << "%" << std::endl;
std::cout << "4. number of valid entries = " << esize << std::endl;
std::cout << "5. number of photons in all valid entries = " << x_ms.size() << std::endl;
std::cout << "6. number of photons in all entries = " << refsize << std::endl;
}