void totalgraph() {

double dist[14] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140};
double sim1[14] = {6.558, 5.129, 4.204, 3.541, 3.072, 2.577, 2.196, 1.893, 1.739, 1.521, 1.405, 1.267, 1.265, 1.209};
double sim2[14] = {7.527, 6.58, 5.713, 5.151, 4.697, 4.305, 3.911, 3.682, 3.465, 3.294, 3.186, 3.066, 3.001, 2.927};
double sim3[14] = {7.464, 6.567, 5.787, 5.109, 4.613, 4.244, 3.937, 3.673, 3.46, 3.274, 3.142, 3.114, 3, 2.96};
double exp[14] = {6.52, 5.28, 4.66, 4.33, 4.14, 3.77, 3.65, 3.53, 3.48, 3.46, 3.32, 3.33, 3.34, 3.41};
double experr[14] = {0.62, 0.6, 0.71, 0.68, 0.6, 0.59, 0.46, 0.51, 0.45, 0.39, 0.36, 0.32, 0.4, 0.43};

TCanvas *c1 = new TCanvas();
c1 -> SetGrid();

TGraph *grb = new TGraphErrors(14, dist, exp, nullptr, experr);
grb -> SetFillColor(2);
grb -> SetFillStyle(3002);
grb -> SetLineColor(kRed);
grb -> GetYaxis() -> SetRangeUser(1, 17);
grb -> SetTitle("NPE vs Distance;Distance (cm);NPE");
grb -> Draw("a3");
grb -> GetYaxis() -> SetRangeUser(1, 8);

TGraph *gr1 = new TGraph(14, dist, sim1);
gr1 -> SetMarkerStyle(21);
gr1 -> SetMarkerColor(kBlack);
gr1 -> SetLineColor(kBlack);
gr1 -> SetLineWidth(2);
gr1 -> Draw("LP SAME");

TGraph *gr2 = new TGraph(14, dist, sim2);
gr2 -> SetMarkerStyle(21);
gr2 -> SetMarkerColor(kBlue);
gr2 -> SetLineColor(kBlue);
gr2 -> SetLineWidth(2);
gr2 -> Draw("LP SAME");

TGraph *gr3 = new TGraph(14, dist, sim3);
gr3 -> SetMarkerStyle(21);
gr3 -> SetMarkerColor(209);
gr3 -> SetLineColor(209);
gr3 -> SetLineWidth(2);
gr3 -> Draw("LP SAME");

TLegend *legend = new TLegend(0.6, 0.6, 0.9, 0.9);
legend -> AddEntry(gr1, "LUTDAVIS Only", "lp");
legend -> AddEntry(gr2, "Adjusted Reflectivity (unified)", "lp");
legend -> AddEntry(gr3, "Adjusted Reflectivity (glisur)", "lp");
legend -> AddEntry(grb, "Experiment", "f");
legend -> Draw();

c1 -> Modified();
c1 -> Update();
}

