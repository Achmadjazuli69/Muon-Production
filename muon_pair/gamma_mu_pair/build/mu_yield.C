void mu_yield()
{
    // ===== USER SETTINGS =====
    double bias  = 1e6;      // cross-section bias factor
    int    nbins = 100;
    double Emin  = 0.0;      // GeV
    double Emax  = 10.0;     // GeV
    // ==========================

    // Open file
    TFile *f = new TFile("muons.root");
    TTree *t = (TTree*)f->Get("muonTree");

    if(!t) {
        std::cout << "Tree not found!" << std::endl;
        return;
    }

    // Automatically determine number of primaries
    double Nprim = t->GetMaximum("eventID") + 1;

    std::cout << "Number of primary electrons = "
              << Nprim << std::endl;

    // Create histogram in GeV
    TH1D *hE = new TH1D("hE",
        "Muon Energy Spectrum per Primary Electron",
        nbins, Emin, Emax);

    // Fill histogram (convert MeV → GeV)
    t->Draw("energy/1000.0 >> hE","","goff");

    // Normalize per electron
    hE->Scale(1.0/Nprim);

    // Correct bias
    hE->Scale(1.0/bias);

    // Convert to differential distribution (per GeV)
    double binWidth = hE->GetBinWidth(1);
    hE->Scale(1.0/binWidth);

    // ===== Style =====
    TCanvas *c = new TCanvas("c","Muon Yield",800,600);
    c->SetLogy();

    hE->SetLineWidth(1);
    hE->SetLineColor(kBlack);

    hE->GetXaxis()->SetTitle("Energy (GeV)");
    hE->GetYaxis()->SetTitle("1/N_{0} dN_{#mu}/dE  (1/GeV)");

    hE->Draw("hist");

    // Print total yield
    double totalYield = hE->Integral("width");

    std::cout << "----------------------------------" << std::endl;
    std::cout << "Total muon yield per electron = "
              << totalYield << std::endl;
    std::cout << "----------------------------------" << std::endl;
}
