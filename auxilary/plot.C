
#include "variables.C"
//#include "correlations.C"
//#include "efficiencies.C"
//#include "mvas.C"
//#include "mutransform.C"


void plot()
{
      const int n_bins = 3;
      TString pt_bin[n_bins] = {"200to350", "350to450", "450above"}

      for(int i=0; i<n_bins; i++){
         
         TString fin = pt_bin[i]+"/TMVA.root";
         TString outBin = pt_bin[i];

	 cout << "=== execute: variables()" << endl;
      	 variables( fin , outBin);

	 //cout << "=== execute: correlations()" << endl;
	 //correlations( fin );

	 //cout << "=== execute: mvas()" << endl;
	 //mvas( fin );

	 //cout << "=== execute: efficiencies()" << endl;
	 //efficiencies( fin );

	 //cout << "=== execute: ztransform()" << endl;
	 //mutransform( fin );
      }

}
