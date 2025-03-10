void graph() {

    double x[14] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140};
    double y1[14] = {13.7012,13.4825,13.2495,12.8691,12.8794,12.4448,12.3847,12.299,12.0438,11.9354,11.9286,11.8556,11.7526,11.5283};
    double y2[14] = {11.7702,11.0582,10.5018,10.1752,9.64793,9.34263,9.04249,8.76,8.57552,8.35852,8.16062,8.02551,7.88765,7.77091};
    double y3[14] = {10.4456,9.74543,9.05813,8.5639,7.94459,7.57699,7.15867,6.91647,6.59905,6.38216,6.23436,6.1248,6.05726,5.94249};
    double y4[14] = {10.0957,9.0004,8.25953,7.47404,6.91017,6.34549,5.90388,5.48859,5.24199,4.94141,4.74232,4.46541,4.39699,4.26522};
    double y5[14] = {9.21624,8.08113,7.27569,6.52269,5.96738,5.32107,4.96877,4.5857,4.29741,3.88768,3.7199,3.51435,3.30452,3.21831};

    TGraph *gr1 = new TGraph(14, x, y1);
    gr1->SetMarkerStyle(8);
    gr1->SetMarkerColor(kBlack);
    gr1->SetLineColor(kBlack);
    gr1->SetLineWidth(2);

    TGraph *gr2 = new TGraph(14, x, y2);
    gr2->SetMarkerStyle(22);
    gr2->SetMarkerSize(2);
    gr2->SetMarkerColor(kRed);
    gr2->SetLineColor(kRed);
    gr2->SetLineWidth(2);

    TGraph *gr3 = new TGraph(14, x, y3);
    gr3->SetMarkerStyle(3);
    gr3->SetMarkerSize(2);
    gr3->SetMarkerColor(kBlue);
    gr3->SetLineColor(kBlue);
    gr3->SetLineWidth(2);

    TGraph *gr4 = new TGraph(14, x, y4);
    gr4->SetMarkerStyle(47);
    gr4->SetMarkerSize(2);
    gr4->SetMarkerColor(kGreen);
    gr4->SetLineColor(kGreen);
    gr4->SetLineWidth(2);

    TGraph *gr5 = new TGraph(14, x, y5);
    gr5->SetMarkerStyle(34);
    gr5->SetMarkerSize(2);
    gr5->SetMarkerColor(kMagenta);
    gr5->SetLineColor(kMagenta);
    gr5->SetLineWidth(2);

    TCanvas *c1 = new TCanvas("c1", "Photon Number vs Distance", 800, 600);
    TMultiGraph *mg = new TMultiGraph();

    mg->Add(gr1);
    mg->Add(gr2);
    mg->Add(gr3);
    mg->Add(gr4);
    mg->Add(gr5);

    mg->SetMinimum(0);

    mg->Draw("ALP");
    mg->SetTitle("Photon Number vs Distance (With QE);Distance from PMT (cm);Number of Photons");

    auto legend = new TLegend(0.7, 0.7, 0.9, 0.9);
    legend->AddEntry(gr1, "Reflectivity 99%", "lp");
    legend->AddEntry(gr2, "Reflectivity 98%", "lp");
    legend->AddEntry(gr3, "Reflectivity 97%", "lp");
    legend->AddEntry(gr4, "Reflectivity 96%", "lp");
    legend->AddEntry(gr5, "Reflectivity 95%", "lp");
    legend->Draw();

    c1->Update();
}
