#ifndef HISTOGRAM_H_
#define HISTOGRAM_H_

#include <iostream>
#include <fstream>

class Histogram {
public:
	int nbin; // number of bins
	double *bin; // number of data in a bin 
	double min,max; // range of the histogram
	double delta; // amplitude of a bin
	double mean1,mean2; // counters for the mean and the mean squared
	double count; // number of counts
	double COUNT_OVER,COUNT_UNDER; // overflows & underflows

	
	Histogram():nbin(0){};
	Histogram(const int Nbin, double min, double max);
	~Histogram();
	
/* adds a value to the histogram */
	void add_value(double const &val);
	void sum(Histogram const &his);

/* calculates average and variance for the histogram */
	double mean(); 
	double variance();
	
/* print out of the normalized probability distribution */
	void print_pdf(FILE* fp);
	void print_pdf(char* name)
	{FILE *fp=fopen(name,"w"); this->print_pdf(fp); fclose(fp);}

//	stream operators
friend std::ostream& operator<<(std::ostream& output, const Histogram& hist);
friend std::istream& operator>>(std::istream& input, Histogram& hist);
	bool write(char *namefile);
	bool read(char *namefile);

};

class Pdf {
public:
	int nbin; // number of bins
	double *bin; // number of data in a bin 
	double min,max; // range of the histogram
	double delta; // amplitude of a bin

	
	Pdf():nbin(0){};
	Pdf(const int Nbin, double min, double max);
	~Pdf();
	
    void normalize();
	bool get(const double &x, double &ret);
	bool set(const double &x, const double& val);
	
/* print out of the normalized probability distribution */
	void print_pdf(FILE* fp);
	void print_pdf(char* name)
	{FILE *fp=fopen(name,"w"); this->print_pdf(fp); fclose(fp);}

//	stream operators
friend std::ostream& operator<<(std::ostream& output, const Pdf& pdf);
friend std::istream& operator>>(std::istream& input, Pdf& pdf);
	bool write(char *namefile);
	bool read(char *namefile);

};


// prototypes 




#endif /*HISTOGRAM_H_*/
