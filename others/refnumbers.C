void refnumbers()
{
fstream file;
file.open("numbers_nt_event.csv", ios::in);
std::vector<double> m_y;
double y;

std::string line;
while (std::getline(file, line)){
std::stringstream sts(line);

std::string a, b, c, d, e, f;
if (std::getline(sts, a, ',') && std::getline(sts, b, ',') && std::getline(sts, c, ',') && std::getline(sts, d, ',') && std::getline(sts, e, ',') && std::getline(sts, f, ','))
{
y = std::stod(f);
m_y.push_back(y);
}
if(file.eof()) break;
}
file.close();

TH1F *hs = new TH1F("hist","Optical Photon Number of Reflections",100, 0, 2000);

for (double y : m_y){
hs -> Fill(y);
}
TCanvas *c1 = new TCanvas();
hs -> GetXaxis() -> SetTitle("Reflection Number");
hs -> GetYaxis() -> SetTitle("Number of Entries");
hs -> SetLineWidth(2);
hs -> SetLineColor(kBlack);
hs -> SetFillColor(38);
hs -> Draw();
}
