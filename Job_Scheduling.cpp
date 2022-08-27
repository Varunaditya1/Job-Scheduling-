#include <iostream>
using namespace std;

// Defining a data-type using class for the jobs
class job_s
{
public:
    int time_submitted;
    int job_no;
    int job_priority;
    int TRC;
};

// Function to display the Time
void display_time(job_s *JOB, int size)
{
    int Time = 0;
    for (int i = 0; i < size; i++)
    {
        Time = Time + 1;
        cout << Time << "-";
        Time = Time + JOB[i].TRC - 1;
        cout << Time << " ";
    }
    cout << endl;
}

// Function to display the  job no.s
void display(job_s *JOB, int size)
{
    for (int i = 0; i < size; i++)
    {
        cout << JOB[i].job_no << " ";
    }
    cout << endl;
}
// Function which return bool value based on the given priority conditions
bool scheduling_policy(job_s *JOB, int parent, int node)
{
    if (JOB[parent].job_priority == JOB[node].job_priority)
    {
        if ((JOB[parent].TRC == JOB[node].TRC) && (JOB[parent].time_submitted > JOB[node].time_submitted))
        {
            return 1;
        }
        if (JOB[parent].TRC < JOB[node].TRC)
        {
            return 1;
        }
    }
    else if (JOB[parent].job_priority > JOB[node].job_priority)
    {
        return 1;
    }
    else
    {
        return 0;
    }
    return 0;
}
// Heapify function

void heapify(job_s *JOB, int n, int s)
{
    int parent, l, r;

    parent = s;
    l = 2 * s + 1;
    r = 2 * (s + 1);
    if ((l < n) && (scheduling_policy(JOB, parent, l) == 0))
    {
        parent = l;
    }
    if ((r < n) && (scheduling_policy(JOB, parent, r) == 0))
    {
        parent = r;
    }
    if (parent != s)
    {
        swap(JOB[parent], JOB[s]);
        heapify(JOB, n, parent);
    }
}
// Function for heap sorting
void heapSort(job_s *JOB, int n)
{
    for (int i = (n / 2) - 1; i >= 0; i--)
    {
        heapify(JOB, n, i);
    }
    for (int i = n - 1; i > 0; i--)
    {
        swap(JOB[0], JOB[i]); // swap last element with first
        heapify(JOB, i, 0);
    }
}
// Function to store kth index at s , and shift all middle indexes to right
void rearranging(job_s *job, int s, int k)
{
    job_s temp = job[k];
    for (int i = k - 1; i >= s; i--)
    {
        // swap(job[i],)
        job[i + 1] = job[i];
    }
    job[s] = temp;
}
// Funtion to make sure element is added if its time submitted is less than current time
void time_sort(job_s *job)
{
    int ct = 1;
    for (int i = 0; i < 10; i++)
    {
        ct += job[i].TRC;
        if ((job[i + 1].time_submitted > ct) && i != 10)
        {
            int k = i + 1;
            while ((job[k].time_submitted > ct) && k < 11)
            {
                k++;
            }
            rearranging(job, i + 1, k);
        }
    }
}
int main()
{
    job_s job[12];
    // Entering data in the array
    job[0] = {0, 1, 2, 30};
    job[1] = {0, 2, 3, 20};
    job[2] = {0, 3, 1, 40};
    job[3] = {0, 4, 2, 10};
    job[4] = {0, 5, 1, 25};
    job[5] = {0, 6, 2, 20};
    job[6] = {25, 7, 2, 35};
    job[7] = {60, 8, 1, 30};
    job[8] = {70, 9, 3, 30};
    job[9] = {150, 10, 2, 20};
    job[10] = {190, 11, 1, 20};
    job[11] = {210, 12, 2, 20};

    // using sort based on only priority
    heapSort(job, 12);
    time_sort(job);
    display(job, 12);
    display_time(job, 12);
}