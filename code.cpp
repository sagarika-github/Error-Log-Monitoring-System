#include <bits/stdc++.h>

using namespace std;
using namespace chrono;

/**
 * @brief Macros To Streamline The Coding Process
 */

#define endl "\n"
#define ff first
#define ss second
#define all(x) (x).begin(), (x).end()

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

/**
 * @brief Server Log Class Representing The Logs As A Real Object
 *        Private Data Members With Getters And Setters Promoting Encapsulation Principle
 */
class ServerLog
{
private:
    long long timestamp;
    string type;
    float severity;

public:
    ServerLog(long long _timestamp, string _type, float _severity)
    {
        this->timestamp = _timestamp;
        this->type = _type;
        this->severity = _severity;
    }

    void showLog()
    {
        cout << this->timestamp << " " << this->type << " " << this->severity << endl;
    }

    long long getTimestamp()
    {
        return this->timestamp;
    }

    void setTimestamp(long long _timestamp)
    {
        this->timestamp = _timestamp;
    }

    string getType()
    {
        return this->type;
    }

    void setType(string _type)
    {
        this->type = _type;
    }

    float getSeverity()
    {
        return this->severity;
    }

    void setSeverity(float _severity)
    {
        this->severity = _severity;
    }
};

vector<ServerLog> logStore;

/**
 * @brief Data Structures Required For Efficiently Answering Type 2 Queries
 */
map<string, pair<float, long long>> sumAndCountOfTypeStore;
map<string, float> maxOfTypeStore;
map<string, float> minOfTypeStore;

/**
 * @brief Data Structures Required For Efficiently Answering Type 3 Queries
 */
vector<pair<long long, float>> timestampWithSeverity;
vector<pair<long long, float>> timestampWithSeveritySum;
vector<pair<long long, float>> timestampWithSeverityMin;
vector<pair<long long, float>> timestampWithSeverityMax;

/**
 * @brief Data Structures Required For Efficiently Answering Type 4 Queries
 */
map<string, vector<pair<long long, float>>> timestampTypeStore;
map<string, vector<pair<long long, float>>> timestampTypeStoreSum;
map<string, vector<pair<long long, float>>> timestampTypeStoreMin;
map<string, vector<pair<long long, float>>> timestampTypeStoreMax;

void processForType2Queries(ServerLog serverLog)
{
    long long timestamp = serverLog.getTimestamp();
    string type = serverLog.getType();
    float severity = serverLog.getSeverity();

    /**
     * @brief Processing Before Answering Type 2 Queries
     */
    if (!sumAndCountOfTypeStore.count(type))
    {
        sumAndCountOfTypeStore[type] = {severity, 1ll};
    }
    else
    {
        sumAndCountOfTypeStore[type].ff += severity;
        sumAndCountOfTypeStore[type].ss += 1ll;
    }

    if (!minOfTypeStore.count(type))
    {
        minOfTypeStore[type] = severity;
    }
    else
    {
        minOfTypeStore[type] = min(minOfTypeStore[type], severity);
    }

    if (!maxOfTypeStore.count(type))
    {
        maxOfTypeStore[type] = severity;
    }
    else
    {
        maxOfTypeStore[type] = max(maxOfTypeStore[type], severity);
    }
}

void processForType3Queries(ServerLog serverLog)
{
    long long timestamp = serverLog.getTimestamp();
    string type = serverLog.getType();
    float severity = serverLog.getSeverity();

    /**
     * @brief Processing Before Answering Type 3 Queries
     */

    timestampWithSeverity.push_back(make_pair(timestamp, severity));
    timestampWithSeveritySum.push_back(make_pair(timestamp, severity));
    timestampWithSeverityMin.push_back(make_pair(timestamp, severity));
    timestampWithSeverityMax.push_back(make_pair(timestamp, severity));

    int len = timestampWithSeverity.size();
    if (len > 1)
    {
        /**
         * @brief Computing Prefix Sum, Minimum And Maximum.
         *        To Answer Type 3 BEFORE Queries In O(1) Access
         */
        timestampWithSeveritySum[len - 1].ss += timestampWithSeveritySum[len - 2].ss;
        timestampWithSeverityMin[len - 1].ss = min(timestampWithSeverityMin[len - 2].ss, timestampWithSeverityMin[len - 1].ss);
        timestampWithSeverityMax[len - 1].ss = max(timestampWithSeverityMax[len - 2].ss, timestampWithSeverityMax[len - 1].ss);
    }
}

void processForType4Queries(ServerLog serverLog)
{
    long long timestamp = serverLog.getTimestamp();
    string type = serverLog.getType();
    float severity = serverLog.getSeverity();

    /**
     * @brief Processing Before Answering Type 4 Queries
     */
    timestampTypeStore[type].push_back(make_pair(timestamp, severity));
    timestampTypeStoreSum[type].push_back(make_pair(timestamp, severity));
    timestampTypeStoreMin[type].push_back(make_pair(timestamp, severity));
    timestampTypeStoreMax[type].push_back(make_pair(timestamp, severity));

    int typeLen = timestampTypeStore[type].size();
    if (typeLen > 1)
    {
        /**
         * @brief Computing Prefix Sum, Minimum And Maximum.
         *        To Answer Type 3 BEFORE Queries In O(log(Number Of Types)) Access
         */
        timestampTypeStoreSum[type][typeLen - 1].ss += timestampTypeStoreSum[type][typeLen - 2].ss;
        timestampTypeStoreMin[type][typeLen - 1].ss = min(timestampTypeStoreMin[type][typeLen - 2].ss, timestampTypeStoreMin[type][typeLen - 1].ss);
        timestampTypeStoreMax[type][typeLen - 1].ss = max(timestampTypeStoreMax[type][typeLen - 2].ss, timestampTypeStoreMax[type][typeLen - 1].ss);
    }
}

void processAndStoreLog(string logInput)
{
    long long timestamp;
    string type;
    float severity;

    stringstream ss(logInput);
    string temp;
    getline(ss, temp, ';');
    timestamp = stoll(temp);
    getline(ss, type, ';');
    getline(ss, temp, ';');
    severity = stof(temp);

    ServerLog serverLog(timestamp, type, severity);

    logStore.push_back(serverLog);

    processForType2Queries(serverLog);

    processForType3Queries(serverLog);

    processForType4Queries(serverLog);
}

void solve()
{
    int type;
    while (cin >> type)
    {
        if (type == 1)
        {
            string s;
            cin >> s;

            processAndStoreLog(s);

            cout << "No output" << endl;
        }
        else if (type == 2)
        {
            string logType;
            cin >> logType;

            if (!sumAndCountOfTypeStore.count(logType))
            {
                cout << "Min: " << 0.0f << ", Max: " << 0.0f << ", Mean: " << 0.0f << endl;
                continue;
            }

            float mean = (float)sumAndCountOfTypeStore[logType].ff / (float)sumAndCountOfTypeStore[logType].ss;
            float mini = minOfTypeStore[logType];
            float maxi = maxOfTypeStore[logType];

            cout << "Min: " << fixed << setprecision(6) << mini << ", Max: " << fixed << setprecision(6) << maxi << ", Mean: " << fixed << setprecision(6) << mean << endl;
        }
        else if (type == 3)
        {
            string when;
            cin >> when;
            long long tstamp;
            cin >> tstamp;
            /**
             * @brief Binary Searching For The Required Timestamp And Storing It For Further Computations
             *        Using Built in C++ Library Functions
             */
            if (when == "BEFORE")
            {
                int idx = lower_bound(all(timestampWithSeveritySum), make_pair(tstamp, 0.0f)) - timestampWithSeveritySum.begin();
                idx--;

                if (idx == -1)
                {
                    cout << "Min: " << 0.0f << ", Max: " << 0.0f << ", Mean: " << 0.0f << endl;
                    continue;
                }

                float mean = (float)timestampWithSeveritySum[idx].ss / (float)(idx + 1);
                float mini = timestampWithSeverityMin[idx].ss;
                float maxi = timestampWithSeverityMax[idx].ss;

                cout << "Min: " << fixed << setprecision(6) << mini << ", Max: " << fixed << setprecision(6) << maxi << ", Mean: " << fixed << setprecision(6) << mean << endl;
            }
            else
            {
                int idx = upper_bound(all(timestampWithSeveritySum), make_pair(tstamp, 0.0f)) - timestampWithSeveritySum.begin();

                if (idx >= timestampWithSeverity.size())
                {
                    cout << "Min: " << 0.0 << ", Max: " << 0.0 << ", Mean: " << 0.0 << endl;
                    continue;
                }

                float mean = 0.0;
                float mini = timestampWithSeverity[idx].ss;
                float maxi = timestampWithSeverity[idx].ss;

                for (int i = idx; i < timestampWithSeverity.size(); i++)
                {
                    mean += timestampWithSeverity[i].ss;
                    mini = min(mini, timestampWithSeverity[i].ss);
                    maxi = max(maxi, timestampWithSeverity[i].ss);
                }

                mean = (float)mean / (float)(timestampWithSeverity.size() - idx);

                cout << "Min: " << fixed << setprecision(6) << mini << ", Max: " << fixed << setprecision(6) << maxi << ", Mean: " << fixed << setprecision(6) << mean << endl;
            }
        }
        else
        {
            string when, logType;
            cin >> when >> logType;
            long long tstamp;
            cin >> tstamp;
            /**
             * @brief Binary Searching For The Required Timestamp And Storing It For Further Computations
             *        Using Built in C++ Library Functions
             */
            if (when == "BEFORE")
            {

                int idx = lower_bound(all(timestampTypeStoreSum[logType]), make_pair(tstamp, 0.0f)) - timestampTypeStoreSum[logType].begin();
                idx--;
                if (idx == -1)
                {
                    cout << "Min: " << 0.0f << ", Max: " << 0.0f << ", Mean: " << 0.0f << endl;
                    continue;
                }
                float mean = (float)timestampTypeStoreSum[logType][idx].ss / (float)(idx + 1);
                float mini = timestampTypeStoreMin[logType][idx].ss;
                float maxi = timestampTypeStoreMax[logType][idx].ss;

                cout << "Min: " << fixed << setprecision(6) << mini << ", Max: " << fixed << setprecision(6) << maxi << ", Mean: " << fixed << setprecision(6) << mean << endl;
            }
            else
            {

                int idx = upper_bound(all(timestampTypeStoreSum[logType]), make_pair(tstamp, 0.0f)) - timestampTypeStoreSum[logType].begin();
                if (idx >= timestampTypeStore[logType].size())
                {
                    cout << "Min: " << 0.0 << ", Max: " << 0.0 << ", Mean: " << 0.0 << endl;
                    continue;
                }
                float mean = 0.0;
                float mini = timestampTypeStore[logType][idx].ss;
                float maxi = timestampTypeStore[logType][idx].ss;

                for (int i = idx; i < timestampTypeStore[logType].size(); i++)
                {
                    mean += timestampTypeStore[logType][i].ss;
                    mini = min(mini, timestampTypeStore[logType][i].ss);
                    maxi = max(maxi, timestampTypeStore[logType][i].ss);
                }

                mean = (float)mean / (float)(timestampTypeStore[logType].size() - idx);
                cout << "Min: " << fixed << setprecision(6) << mini << ", Max: " << fixed << setprecision(6) << maxi << ", Mean: " << fixed << setprecision(6) << mean << endl;
            }
        }
    }
}
int32_t main()
{
    /**
     * @brief Doing I/O Through File Handling As Instructed.
     *
     */
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    freopen("error.txt", "w", stderr);

    /**
     * @brief Fast I/O Since We Are Taking And Printing A Lot Of Content
     */
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    auto start1 = high_resolution_clock::now();

    solve();

    auto stop1 = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop1 - start1);
    cerr << "Time : " << duration.count() / 1000 << endl;
    
    return 0;
}