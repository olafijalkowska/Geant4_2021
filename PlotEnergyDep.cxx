void PlotEnergyDep()
{
    //otwarcie pliku
    TFile* f = new TFile("NaIDetOutput.root");
    TTree* t=(TTree*)f->Get("NaIInfo");

    double xMin = 0;
    double xMax = 520;
    int nBins = 1*(xMax-xMin);
    TH1F* energy = new TH1F("energy","energy",nBins,xMin,xMax);
    //możemy stawiać bramki na innych gałęziach
    TCut cut = "detectorId < 20";
    t->Draw("energyDep*1000>>energy",cut);
    gPad->SetLogy();
    energy->Draw();
}
