#include	"FastRegression.cpp"
#include	<algorithm>
#include	<iostream>
#include	<fstream>
#include	<cfloat>
#include	<vector>
#include	<cmath>
using	namespace	std;
struct	Data{	double	x,	y;	};
vector<Data>	data;

bool	load_data(const	char	*F){
	ifstream	fi(F);
	if(!fi)	return	false;
	string	s;	fi>>s>>s;	Data	d;
	for(fi>>d.x>>d.y;	!fi.eof();	fi>>d.x>>d.y)	data.push_back(d);
	fi.close();
	return	true;
}

double	model_r2(double	alpha){
	double	sx=0,	sxx=0,	sy=0,	syy=0,	sxy=0,	sn=data.size()-0;
	for(size_t	i=0;	i<data.size();	i++){
		double	x=i,	y=log(data[i].y+alpha);
		sx+=x;	sxx+=x*x;	sy+=y;	syy+=y*y;	sxy+=x*y;
	}
	sx/=sn;	sy/=sn;
	return	(sxy/sn-sx*sy)*(sxy/sn-sx*sy)/(sxx/sn-sx*sx)/(syy/sn-sy*sy);
}

int	main(void){
	if(!load_data("data.txt"))	return	0;
	double	ba=0,	br2=0;
	for(size_t	i=0;	i<1000;	i++){	double	r2=model_r2(i);	if(r2>br2){	br2=r2;	ba=i;	}	}
	FastRegression	fr;	fr.clear();
	for(size_t	i=0;	i<data.size();	i++)	fr.push2(1,log10(data[i].y+ba),data[i].x);
	fr.estimate(2);
//	cerr<<"N(t) + "<<ba<<" = "<<exp(fr.c)<< " * exp( "<<fr.a<<" * t )\n";
	cout<<fr.a<<'\t'<<fr.c<<'\n';
	ofstream	fo("table.txt");
	fo<<"|Feburary|Diagnosis|Model|\n|----|----|----|\n";
	for(size_t	i=0;	i<data.size();	i++){
		fo<<"|"<<data[i].x<<"|"<<data[i].y<<"|"<<exp(fr.c)*exp(fr.a*data[i].x)-ba<<"|\n";
	}
	fo.close();
	fo.open("plot.txt");
	for(size_t  i=0;    i<data.size();  i++)	fo<<data[i].x<<'\t'<<log10(data[i].y+ba)<<'\n';
	fo.close();
	return	0;
}
