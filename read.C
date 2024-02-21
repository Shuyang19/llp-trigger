#include <iostream>
#include "TFile.h"
#include "TH1F.h"
#include "TTree.h"
#include "TCanvas.h"

void read() {
    // Open the ROOT file
    TFile *file = TFile::Open("BToKPhi_MuonLLPDecayGenFilter_PhiToPi0Pi0_mPhi0p3_ctau1000.root");
    if (!file || file->IsZombie()) {
        std::cerr << "Error opening file" << std::endl;
        return;
    }

    // Get the TTree from the file
    TTree *tree = nullptr;
    file->GetObject("MuonSystem", tree);
    if (!tree) {
        std::cerr << "Error retrieving MuonSystem TTree" << std::endl;
        file->Close();
        return;
    }

    // set your binning
    TH1F *h_gLLP_ctau = new TH1F("h_gLLP_ctau", "h_gLLP_ctau", 100, 0, 1000);

    // Set branch address
    float gLLP_ctau;
    tree->SetBranchAddress("gLLP_ctau", &gLLP_ctau);

    // Loop over the tree entries and fill the histogram
    Long64_t nEntries = tree->GetEntries();
    for (Long64_t i = 0; i < nEntries; i++) {
        tree->GetEntry(i);
        h_gLLP_ctau->Fill(gLLP_ctau);
    }

    // Now you can use the histograms you saved in the loop here



    // For Plotting
    TCanvas *c1 = new TCanvas("c1", "gLLP_ctau Distribution", 800, 600);
    h_gLLP_ctau->Draw();

    // Save the canvas to a file
    c1->SaveAs("h_gLLP_ctau.png");
    c1->SetLogy();
    c1->SaveAs("h_gLLP_ctau_log.png");

    // Close the ROOT file
    file->Close();
}

