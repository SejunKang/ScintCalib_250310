void angle() {
std::vector<double> x;
fstream file;
file.open("numbers_nt_num.csv", ios::in);
std::string line;
while (std::getline(file, line))
{
    std::stringstream sts(line);
    std::string a, b, c;
    if (std::getline(sts, a, ',') && std::getline(sts, b, ',') && std::getline(sts, c, ','))
    {
        
        double angle = std::stod(c);
        x.push_back(angle);
    }
}
file.close();

TH1F *h1 = new TH1F("h1", "Incident angle distribution", 100, 0, 1);
for (double x_m : x) {
h1 -> Fill(x_m);
}
TCanvas *c1 = new TCanvas();
c1 -> SetGrid();
h1 -> GetXaxis() -> SetTitle("cos #theta");
h1 -> SetLineWidth(2);
h1->Draw();

}
