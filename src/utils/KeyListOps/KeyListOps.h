/*
 * KeyListOps.h
 *
 *  Created on: Feb 6, 2014
 *      Author: nek3d
 */

#ifndef KEYLISTOPS_H_
#define KEYLISTOPS_H_

using namespace std;

#include <map>
#include <utility> //for pair
#include "QuickString.h"
#include <stdint.h>
#include "RecordKeyList.h"

class KeyListOps {
public:
	KeyListOps();
	KeyListOps(RecordKeyList *keyList, int column = 1);
	~KeyListOps();


	void setKeyList(RecordKeyList *keyList) { _keyList = keyList; }
	void setColumn(int col) { _column = col; }
	void setNullValue(const QuickString & nullVal) { _nullVal = nullVal; }
	void setDelimStr(const QuickString &delimStr) { _delimStr = delimStr; }


    typedef enum { SUM, MEAN, STDDEV, SAMPLE_STDDEV, MEDIAN, MODE, ANTIMODE, MIN, MAX, ABSMIN, ABSMAX, COUNT, DISTINCT, COUNT_DISTINCT,
    	DISTINCT_ONLY, COLLAPSE, CONCAT, FREQ_ASC, FREQ_DESC, FIRST, LAST, INVALID } OP_TYPES;

    OP_TYPES getOpCode(const QuickString &operation) const;
    // return the total of the values in the vector
    double getSum();
    // return the average value in the vector
    double getMean();
     // return the standard deviation
    double getStddev();
    // return the sample standard deviation
    double getSampleStddev();
    // return the median value in the vector
    double getMedian();
    // return the most common value in the vector
    const QuickString &getMode();
    // return the least common value in the vector
    const QuickString &getAntiMode();
    // return the minimum element of the vector
    double getMin();
    // return the maximum element of the vector
    double getMax();
    // return the minimum absolute value of the vector
    double getAbsMin();
    // return the maximum absolute value of the vector
    double getAbsMax();
    // return the count of element in the vector
    uint32_t getCount();
    // return a the count of _unique_ elements in the vector
    uint32_t getCountDistinct();
    // return only those elements that occur once
    const QuickString &getDistinctOnly();
    // return a delimiter-separated list of elements
    const QuickString & getCollapse(const QuickString & delimiter = ",");
    // return a concatenation of all elements in the vector
    const QuickString & getConcat();
    // return a comma-separated list of the _unique_ elements
    const QuickString & getDistinct();
    // return a histogram of values and their freqs. in desc. order of frequency
    const QuickString & getFreqDesc();
    // return a histogram of values and their freqs. in asc. order of frequency
    const QuickString & getFreqAsc();
    // return the first value in the list
    const QuickString & getFirst();
    // return the last value in the list
    const QuickString & getLast();

private:
	RecordKeyList *_keyList;
	int _column;
	QuickString _nullVal;
	QuickString _delimStr;
	QuickString _retStr;

	map<QuickString, OP_TYPES> _opCodes;
	RecordKeyList _nullKeyList; //this has to exist just so we can initialize _iter, below.
	RecordKeyList::const_iterator_type _iter;

	// Some methods need to put values into a vector, mostly for sorting.
	vector<double> _numArray;
	vector<QuickString> _qsArray;

	typedef map<QuickString, int> freqMapType;
	freqMapType _freqMap;
	freqMapType::iterator _freqIter;

	typedef enum { UNSORTED, ASC, DESC} SORT_TYPE;

	typedef multimap<int, QuickString, less<int> > histAscType;
	typedef multimap<int, QuickString, greater<int> > histDescType;
	void init();
	const QuickString &getColVal();
	double getColValNum();
	bool empty() { return _keyList->empty(); }
	void begin() { _iter = _keyList->begin(); }
	bool end() { return _iter == _keyList->end(); }
	void next() { _iter = _keyList->next(); }
	void toArray(bool useNum, SORT_TYPE sortVal = UNSORTED);
	void sortArray(bool useNum, bool ascOrder);
	void makeFreqMap();


};


#endif /* KEYLISTOPS_H_ */
