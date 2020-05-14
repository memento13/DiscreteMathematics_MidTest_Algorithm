#include <iostream>
#include <string>
#include <vector>
#include <chrono> 
#include <random>
#include <algorithm>
using namespace std;
using namespace chrono;

double BubbleSort(vector<int> &v)// ��������
{
	int n = static_cast<int>(v.size());
	system_clock::time_point start = system_clock::now();//�ð����� ����
	
	while (n > 0) {
		int lastModifiedIndex = 0;
		for (int currentIndex = 1; currentIndex < n; currentIndex++) {
			if (v[currentIndex - 1] > v[currentIndex]) { // ���� �ں��� Ŭ ���
				// ��ȯ
				int temp = v[currentIndex - 1];
				v[currentIndex - 1] = v[currentIndex];
				v[currentIndex] = temp;
				lastModifiedIndex = currentIndex;//��ȯ���θ� ��Ÿ��
			}
		}
		n = lastModifiedIndex;//n=0�� ���� �̹� ���ĵȰ�� �ۿ� ����
	}

	system_clock::time_point end = system_clock::now();//�ð����� ��
	milliseconds milliSec = duration_cast<milliseconds>(end - start);//ƽ�� �и��ʷ� ��ȯ
	return (double)(milliSec.count());
}
//=========================================================================================================
double SelectionSort(std::vector<int> &v) //��������
{
	system_clock::time_point start = system_clock::now();//�ð����� ����

	for (int currentIndex = 0; currentIndex < v.size() - 1; currentIndex++) {
		int minIndex = currentIndex;//���� ���� �ε����� �̴ϸ� �ε����� �ӽ�����
		for (int i = currentIndex + 1; i < v.size(); i++) {//�̴ϸ� �ε��� ã��
			if (v[i] < v[minIndex]) {//�񱳰��� ���� �̴ϸغ��� ������
				minIndex = i; //�̴ϸ��ε��� ����
			}
		}
		if (minIndex != currentIndex) {//������ �ε����� �̴ϸ� �ε����� �ٸ���� �񱳰����� ���� �ε����� �ֱ⶧���� ����
			int temp = v[currentIndex];
			v[currentIndex] = v[minIndex];
			v[minIndex] = temp;
		}
	}

	system_clock::time_point end = system_clock::now();//�ð����� ��
	milliseconds milliSec = duration_cast<milliseconds>(end - start);//ƽ�� �и��ʷ� ��ȯ
	return (double)(milliSec.count());
}

//=========================================================================================================
static int partition_1(vector<int> &v, int startIndex, int endIndex) //������ �߰��� ��Ƽ��
{
	int pivotIndex = (startIndex + endIndex) / 2;
	int pivotValue = v[pivotIndex];//������ ��� �ε����� �Ǻ�
	while (true) {
		while (v[startIndex] < pivotValue) {//left �Ǻ�
			startIndex++;
		}

		while (v[endIndex] >= pivotValue && v[endIndex]>=v[startIndex]) {//right �Ǻ�
			if (startIndex == endIndex) {// �� �Ǻ��� ������ ����̸� �� �Ǻ��� ���� ������ ��ȯ
				return endIndex;
			}
			endIndex--;
		}

		
		// left �� right �Ǻ��� ��ȯ
		int temp = v[startIndex];
		v[startIndex] = v[endIndex];
		v[endIndex] = temp;
	}
}

void QuickSort_1(vector<int> &v, int startIndex, int endIndex) //������ �߰����� �Ǻ����� �ϴ� ������
{
	if (startIndex < endIndex) {
		int pivotIndex = partition_1(v, startIndex, endIndex);// �ѷ� ����
		QuickSort_1(v, startIndex, pivotIndex);//�� ����
		QuickSort_1(v, pivotIndex + 1, endIndex);//�� ����
	}
}
//=========================================================================================================
int FindMid(int a, int b, int c)//�߾Ӱ� ���ϴ� �Լ�
{
	if (a >= b) {
		if (b >= c) return b;
		else if (a <= c) return a;
		else return c;
	}
	else if(a >= c) return a;
	else if (b >= c) return c;
	else return b;
}

static int partition_2(vector<int> &v, int startIndex, int endIndex) //������ ù��,����,�߰����� ���Ͽ� �߾Ӱ��� �Ǻ����� ��� ��Ƽ��
{
	int pivotIndex = (startIndex + endIndex) / 2;
	int pivotValue = FindMid(v[startIndex], v[endIndex], v[pivotIndex]);//�߾Ӱ� �Ǻ�����
	
	while (true) {
		while (v[startIndex] < pivotValue) {//left �Ǻ�
			startIndex++;
		}

		while (v[endIndex] >= pivotValue && v[endIndex] >= v[startIndex]) {//right �Ǻ�
			if (startIndex == endIndex) {// �� �Ǻ��� ������ ����̸� �� �Ǻ��� ���� ������ ��ȯ
				return endIndex;
			}
			endIndex--;
		}
		// left �� right �Ǻ��� ��ȯ
		int temp = v[startIndex];
		v[startIndex] = v[endIndex];
		v[endIndex] = temp;
	}
}

void QuickSort_2(vector<int> &v, int startIndex, int endIndex) //������ �߰����� �Ǻ����� �ϴ� ������
{
	if (startIndex < endIndex) {
		int pivotIndex = partition_2(v, startIndex, endIndex);// �ѷ� ����
		QuickSort_2(v, startIndex, pivotIndex);//�� ����
		QuickSort_2(v, pivotIndex + 1, endIndex);//�� ����
	}
}
//=========================================================================================================
static int partition_worst(vector<int> &v, int startIndex, int endIndex) //���� ó���� �ǹ����� ����
{
	int pivotIndex = startIndex;
	int pivotValue = v[pivotIndex];//������ ���� �� �ε����� �Ǻ�
	while (true) {
		while (v[startIndex] < pivotValue) {//left �Ǻ�
			startIndex++;
		}

		while (v[endIndex] >= pivotValue && v[endIndex] >= v[startIndex]) {//right �Ǻ�
			if (startIndex == endIndex) {// �� �Ǻ��� ������ ����̸� �� �Ǻ��� ���� ������ ��ȯ
				return endIndex;
			}
			endIndex--;
		}


		// left �� right �Ǻ��� ��ȯ
		int temp = v[startIndex];
		v[startIndex] = v[endIndex];
		v[endIndex] = temp;
	}
}

void QuickSort_worst(vector<int> &v, int startIndex, int endIndex) //���� ó������ �Ǻ����� �ϴ� ������
{
	if (startIndex < endIndex) {
		int pivotIndex = partition_worst(v, startIndex, endIndex);// �ѷ� ����
		QuickSort_worst(v, startIndex, pivotIndex);//�� ����
		QuickSort_worst(v, pivotIndex + 1, endIndex);//�� ����
	}
}
//=========================================================================================================
void Merge(vector<int> &v, int start, int middle, int end) 
{

	static vector<int> leftArray(middle - start + 1);
	static vector<int> rightArray(end - middle);

	//���� �迭�� ����
	for (int i = 0; i < leftArray.size(); ++i)
		leftArray[i] = v[start + i];

	// ������ �迭�� ����
	for (int i = 0; i < rightArray.size(); ++i)
		rightArray[i] = v[middle + 1 + i];

	int leftIndex = 0, rightIndex = 0; //���� ������ �ε��� �ʱ�ȭ
	int currentIndex = start;  //���� �迭�� �����ϱ� ���� �迭 ������ ����

	// ���ʰ� ������ �迭 ���ϸ鼭 �����ͺ��� �־� ����
	while (leftIndex < leftArray.size() && rightIndex < rightArray.size()) {
		if (leftArray[leftIndex] <= rightArray[rightIndex]) {//������ �����ʺ��� �񱳰��� ������
			v[currentIndex] = leftArray[leftIndex];
			leftIndex++;
		}
		else {//�������� ���ʺ��� �۰ų� ������
			v[currentIndex] = rightArray[rightIndex];
			rightIndex++;
		}
		currentIndex++;
	}

	// ���� ���ʹ迭 ���� ����
	while (leftIndex < leftArray.size()) v[currentIndex++] = leftArray[leftIndex++];

	//���� ������ �迭 ���� ����
	while (rightIndex < rightArray.size()) v[currentIndex++] = rightArray[rightIndex++];
}


void MergeSort(vector<int> &v, int start, int end) 
{
	if (start < end) {
		// �߰��� ã��
		int middle = (start + end) / 2;

		MergeSort(v, start, middle); // ������ ������ ���� �迭 ����
		MergeSort(v, middle + 1, end);  // ���ʹ迭 ����

		Merge(v, start, middle, end); //���� �� �迭 merge
	}
}
//=========================================================================================================

double ShellSort(vector<int> &v)
{
	system_clock::time_point start = system_clock::now();//�ð����� ����

	for (int gapSize = v.size() / 2; gapSize > 0; gapSize /= 2) {
		for (int currentIndex = gapSize; currentIndex < v.size(); currentIndex++) {
			//���������� ���� �ʱ�ȭ
			int currentIndexCopy = currentIndex;
			int currentIndexValue = v[currentIndex];
			//gap������ �ǳ� ��������
			while (currentIndexCopy >= gapSize && v[currentIndexCopy - gapSize] > currentIndexValue) {
				v[currentIndexCopy] = v[currentIndexCopy - gapSize];
				currentIndexCopy -= gapSize;
			}
			v[currentIndexCopy] = currentIndexValue;
		}
	}

	system_clock::time_point end = system_clock::now();//�ð����� ��
	milliseconds milliSec = duration_cast<milliseconds>(end - start);//ƽ�� �и��ʷ� ��ȯ
	return (double)(milliSec.count());
}

//=========================================================================================================
void pushbackReverse(vector<int>& v, int num) 
{
	for (unsigned int i = num; i > 0; i--) {
		v.push_back(i);
	}
}
void pushbackSorted(vector<int>& v, int num)
{
	for (unsigned int i = 0; i < num; i++) {
		v.push_back(i);
	}
}
void pushbackRandom(vector<int>& v, int num) 
{
	int tmp;
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dis(1, num);
	for (int i = 0; i <num ; i++) {
		tmp = dis(gen);
		v.push_back(tmp);
	}
}
//=========================================================================================================
template<typename Func>
double RandomVectorSortAverage(int testCase, int vectorSize, Func SortType) //�������������� �׽�Ʈ���̽� ��ŭ �����Ͽ� ���� ����ð��� �����Ͽ� ��հ� ��ȯ
{
	
	double result = 0;
	for (int i = 0; i < testCase; i++) {
		vector<int> randomVector;
		pushbackRandom(randomVector, vectorSize);
		result += SortType(randomVector);
		randomVector.clear();
	}
	return result / testCase;
}

template<typename Func>
double ReverseVectorSort(int vectorSize, Func SortType) //������ ������ ���͸� �����Ͽ� ����ð� ��ȯ
{
	vector<int> reverseVector;
	//reverseVector.resize(vectorSize);
	pushbackReverse(reverseVector, vectorSize);
	return SortType(reverseVector);
}

template<typename Func>
double SortedVectorSort(int vectorSize, Func SortType) //������ ������ ���͸� �����Ͽ� ����ð� ��ȯ
{
	vector<int> reverseVector;
	//reverseVector.resize(vectorSize);
	pushbackSorted(reverseVector, vectorSize);
	return SortType(reverseVector);
}

template<typename Func>
double ForQuickSortRandomVectorSortAverage(int testCase, int vectorSize, Func SortType) //�������������� �׽�Ʈ���̽� ��ŭ �����Ͽ� ���� ����ð��� �����Ͽ� ��հ� ��ȯ
{
	
	double result = 0;
	for (int i = 0; i < testCase; i++) {
		vector<int> randomVector;
		pushbackRandom(randomVector, vectorSize);

		system_clock::time_point start = system_clock::now();//�ð����� ����
		SortType(randomVector, 0, (vectorSize - 1));
		system_clock::time_point end = system_clock::now();//�ð����� ��
		milliseconds milliSec = duration_cast<milliseconds>(end - start);//ƽ�� �и��ʷ� ��ȯ
		result += (double)(milliSec.count());
		randomVector.clear();
	}
	return result / testCase;
}
template<typename Func>
double ForQuickSortReverseVectorSort(int vectorSize, Func SortType) //������ ������ ���͸� �����Ͽ� ����ð� ��ȯ
{
	vector<int> reverseVector;
	//reverseVector.resize(vectorSize);
	pushbackReverse(reverseVector, vectorSize);

	system_clock::time_point start = system_clock::now();//�ð����� ����
	SortType(reverseVector, 0, (vectorSize - 1));
	system_clock::time_point end = system_clock::now();//�ð����� ��
	milliseconds milliSec = duration_cast<milliseconds>(end - start);//ƽ�� �и��ʷ� ��ȯ
	
	return (double)(milliSec.count());
}

template<typename Func>
double ForQuickSortSortedVectorSort(int vectorSize, Func SortType) //������ ������ ���͸� �����Ͽ� ����ð� ��ȯ
{
	vector<int> reverseVector;
	//reverseVector.resize(vectorSize);
	pushbackSorted(reverseVector, vectorSize);

	system_clock::time_point start = system_clock::now();//�ð����� ����
	SortType(reverseVector, 0, static_cast<int>(vectorSize - 1));
	system_clock::time_point end = system_clock::now();//�ð����� ��
	milliseconds milliSec = duration_cast<milliseconds>(end - start);//ƽ�� �и��ʷ� ��ȯ

	return (double)(milliSec.count());
}

int main() 
{
	
	cout << "SortedBubbleSort \t" << SortedVectorSort(10000, BubbleSort) << "  ms" << endl;
	cout <<"randomBubbleSort \t"<< RandomVectorSortAverage(5, 10000, BubbleSort) << " ms" << endl;
	cout << "reverseBubbleSort \t"<<ReverseVectorSort(10000, BubbleSort) << "  ms" << endl;
	cout << endl;
	cout << "SortedSelectionSort \t" << SortedVectorSort(10000, SelectionSort) << "  ms" << endl;
	cout << "randomSelectionSort \t" << RandomVectorSortAverage(5, 10000, SelectionSort) << " ms" << endl;
	cout << "reverseSelectionSort \t" << ReverseVectorSort(10000, SelectionSort) << "  ms" << endl;
	cout << endl;
	
	cout << "quckSort_IndexMid_Pivot_Sorted \t\t" << ForQuickSortSortedVectorSort(10000, QuickSort_1) << "ms" << endl;
	cout << "quckSort_IndexMid_Pivot_Random \t\t" << ForQuickSortRandomVectorSortAverage(5, 10000, QuickSort_1) << "ms" << endl;
	cout << "quckSort_IndexMid_Pivot_Reverse \t" << ForQuickSortReverseVectorSort(10000, QuickSort_1) << "ms" << endl;
	cout << endl;
	cout << "quckSort_ValueMid_Pivot_Sorted \t\t" << ForQuickSortSortedVectorSort(10000, QuickSort_2) << "ms" << endl;
	cout << "quckSort_ValueMid_Pivot_Random \t\t" << ForQuickSortRandomVectorSortAverage(5, 10000, QuickSort_2) << "ms" << endl;
	cout << "quckSort_ValueMid_Pivot_Reverse \t" << ForQuickSortReverseVectorSort(10000, QuickSort_2) << "ms" << endl;
	cout << endl;
	
	cout << "quckSort_FirstIndex_Pivot_Sorted \t" << ForQuickSortSortedVectorSort(1000, QuickSort_worst) << "ms" << endl;
	cout << "quckSort_FirstIndex_Pivot_Random \t" << ForQuickSortRandomVectorSortAverage(5, 1000, QuickSort_worst) << "ms" << endl;
	cout << "quckSort_FirstIndex_Pivot_Reverse \t" << ForQuickSortReverseVectorSort(1000, QuickSort_worst) << "ms" << endl;
	cout << endl;


	cout << "MergeSortSorted \t" << ForQuickSortSortedVectorSort(10000, MergeSort) << "ms" << endl;
	cout << "MergeSortRandom \t" << ForQuickSortRandomVectorSortAverage(5, 10000, MergeSort) << "ms" << endl;
	cout << "MergeSortReverse \t" << ForQuickSortReverseVectorSort(10000, MergeSort) << "ms" << endl;
	cout << endl;
	
	cout << "SortedShellSort \t" << SortedVectorSort(10000, ShellSort) << "  ms" << endl;
	cout << "randomShellSort \t" << RandomVectorSortAverage(5, 10000, ShellSort) << " ms" << endl;
	cout << "reverseShellSort \t" << ReverseVectorSort(10000, ShellSort) << "  ms" << endl;
	cout << endl;
	


	string exit;
	while (true) {
		cout << "�����ҷ��� exit �Է�";
		cin >> exit;
		if (exit == "exit")
			return 0;
	}
}