all: covid-19
covid-19:	covid-19.cpp
	g++ covid-19.cpp -o covid-19 -Ofast -Wall -s
