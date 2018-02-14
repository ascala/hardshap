#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Histogram.h"

/* ----------------- HISTOGRAMS ----------------- */

/* creates and initializes a new histogram structure with
 * nbin bins for the range [min, double max] */
Histogram::Histogram(int Nbin, double minval, double maxval){
	nbin=Nbin;
	bin=new double[nbin];
	int i; for (i = 0; i < nbin; ++i) bin[i]=0.0;

	if(minval>maxval){std::cerr<<"'mbecille\n"<<std::flush;exit(-1);}
	min=minval; max=maxval;
	delta=(max-min)/(double)nbin;
	
	COUNT_OVER=COUNT_UNDER=count=0.0;
	mean1=mean2=0.0;
}

/*destructor*/
Histogram::~Histogram(){if(nbin>0) delete[] bin;}


/* adds a value to the histogram */
void Histogram::add_value(double const &val){
	int ibin;
	if(val < min) { ++COUNT_UNDER; return;}
	if(val > max) {++COUNT_OVER; return;}
	mean1 += val; mean2 += val*val;
	ibin = (int)( (val-min)/delta );
	++bin[ibin]; ++count;
	return;
}

void Histogram::sum(Histogram const &his){
	if((min!=his.min)||(max!=his.max)||(nbin!=his.nbin))
	{std::cerr<<"can't sum such histograms!!!\n";exit(1);}
	COUNT_OVER+=his.COUNT_OVER;
	COUNT_UNDER+=his.COUNT_UNDER;
	count+=his.count;
	for (int ibin = 0; ibin < nbin; ++ibin) bin[ibin]+=his.bin[ibin];
	mean1+=his.mean1; mean2+=his.mean2;
}

/* calculates average and variance for the histogram */
double Histogram::mean(){return mean1/count;}
double Histogram::variance(){ double m2=mean2/count, m1=this->mean(); return sqrt(m2-m1*m1);}

/* print out of the normalized probability distribution */
void Histogram::print_pdf(FILE* fp){
	// normalization for p(x)dx
	double dx = delta;
	double norm_fac = 1.0/(count * delta);	
	for (int ibin = 0; ibin < nbin; ++ibin) 
		fprintf(fp,"%g %g\n",
			min+(ibin+0.5)*dx,norm_fac*bin[ibin]);
	return;
}

//	stream operators
std::ostream& operator<<(std::ostream& output, const Histogram& hist){ 
	output << hist.nbin << std::endl;
	output << hist.min << " " << hist.max<< std::endl;
	output << hist.count << std::endl;
	output << hist.mean1 << " " << hist.mean2<< std::endl;
	output << hist.COUNT_OVER << " " << hist.COUNT_UNDER<< std::endl;
	for (int ibin = 0; ibin < hist.nbin; ++ibin) output << hist.bin[ibin] <<std::endl;
	return output; 
}

std::istream& operator>>(std::istream& input, Histogram& hist){ 
	if(hist.nbin>0) delete[] hist.bin;
	input >> hist.nbin; hist.bin = new double[hist.nbin];
	input >> hist.min >> hist.max; hist.delta=(hist.max-hist.min)/(double)hist.nbin;
	input >> hist.count;
	input >> hist.mean1 >> hist.mean2;
	input >> hist.COUNT_OVER >> hist.COUNT_UNDER;
	for (int ibin = 0; ibin < hist.nbin; ++ibin) input >> hist.bin[ibin];
	return input; 
}

bool Histogram::write(char *namefile){
	std::fstream myfile;
    myfile.precision(16);
    
    myfile.open(namefile,std::ios::out);
    myfile<<*this;
    myfile.close();
    	
    return true;
} 	

bool Histogram::read(char *namefile){
	std::fstream myfile;
		
    myfile.open(namefile,std::ios::in);
    myfile >> *this;
    myfile.close();
    	
    return true;
} 	




/* ----------------- PDFs ----------------- */

/* creates and initializes a new pdf structure with
 * nbin bins for the range [min, double max] */
Pdf::Pdf(int Nbin, double minval, double maxval){
	nbin=Nbin;
	bin=new double[nbin];
	int i; for (i = 0; i < nbin; ++i) bin[i]=0.0;

	if(minval>maxval){std::cerr<<"'mbecille\n"<<std::flush;exit(-1);}
	min=minval; max=maxval;
	delta=(max-min)/(double)nbin;
}

/*destructor*/
Pdf::~Pdf(){if(nbin>0) delete[] bin;}



void Pdf::normalize(){
	double norm=0;
	for (int ibin = 0; ibin < nbin; ++ibin) norm+=bin[ibin];
	for (int ibin = 0; ibin < nbin; ++ibin) bin[ibin]/=(norm*delta);
}

bool Pdf::get(const double &x, double &ret){
	if(x<=min) {
		ret=bin[0];
		return false;
	}
	else if(x>=max){
		ret=bin[nbin-1];
		return false;
	}
	else{
		int ibin=(int)((x-min)/delta);
		ret=bin[ibin];
		return true;
	}
}

bool Pdf::set(const double &x, const double& val){
	if((x<min)||(x>max)) return false;
	else{
		int ibin=(int)((x-min)/delta);
		bin[ibin]=val;
		return true;
	}
}
	
/* print out of the pdf */
void Pdf::print_pdf(FILE* fp){
	// normalization for p(x)dx
	double dx = delta;
	for (int ibin = 0; ibin < nbin; ++ibin) 
		fprintf(fp,"%g %g\n",
			min+(ibin+0.5)*dx,bin[ibin]);
	return;
}

//	stream operators
std::ostream& operator<<(std::ostream& output, const Pdf& pdf){ 
	output << pdf.nbin << std::endl;
	output << pdf.min << " " << pdf.max<< std::endl;
	for (int ibin = 0; ibin < pdf.nbin; ++ibin) output << pdf.bin[ibin] <<std::endl;
	return output; 
}

std::istream& operator>>(std::istream& input, Pdf& pdf){ 
	if(pdf.nbin>0) delete[] pdf.bin;
	input >> pdf.nbin; pdf.bin = new double[pdf.nbin];
	input >> pdf.min >> pdf.max; pdf.delta=(pdf.max-pdf.min)/(double)pdf.nbin;
	for (int ibin = 0; ibin < pdf.nbin; ++ibin) input >> pdf.bin[ibin];
	return input; 
}

bool Pdf::write(char *namefile){
	std::fstream myfile;
    myfile.precision(16);
    
    myfile.open(namefile,std::ios::out);
    myfile<<*this;
    myfile.close();
    	
    return true;
} 	

bool Pdf::read(char *namefile){
	std::fstream myfile;
		
    myfile.open(namefile,std::ios::in);
    myfile >> *this;
    myfile.close();
    	
    return true;
} 	
