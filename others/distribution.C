void distribution()
{

std::fstream file;
file.open("entries_nt_ent.csv", std::ios::in);
std::vector<std::tuple<double, double, double>> xyz_ms;
double x,y,z;
TH3F *hist = new TH3F("hist", "Photon Position Distribution", 50, -2.5, 2.5,50, 55, 75,50, -2.5, 2.5);
while(1)
{
std::string line;
while (std::getline(file, line)){
std::stringstream sts(line);

std::string x_str, y_str, z_str;
if (std::getline(sts, x_str, ',') && std::getline(sts, y_str, ',') && std::getline(sts, z_str, ','))
 {
    x = std::stod(x_str);
    y = std::stod(y_str);
    z = std::stod(z_str);
xyz_ms.emplace_back(x,y,z);
}
}
if(file.eof()) break;
}
file.close();
for (const auto& xyz : xyz_ms){
hist->Fill(std::get<0>(xyz), std::get<1>(xyz), std::get<2>(xyz));
}

hist->GetXaxis()->SetTitle("x (cm)");
hist->GetYaxis()->SetTitle("y (cm)");
hist->GetZaxis()->SetTitle("z (cm)");
TCanvas *c1 = new TCanvas();
hist->Draw("SURF");
}
