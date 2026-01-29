#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <random>
#include <iomanip>
using namespace std;

struct Point {
    double x, y;
    int cluster;
    
    Point(double x = 0, double y = 0) : x(x), y(y), cluster(-1) {}
    
    double distanceTo(const Point& other) const {
        return sqrt((x - other.x) * (x - other.x) + (y - other.y) * (y - other.y));
    }
};

class KMeansClustering {
private:
    vector<Point> points;
    vector<Point> centroids;
    int k;
    int maxIterations;
    
public:
    KMeansClustering(int clusters, int maxIter = 100) : k(clusters), maxIterations(maxIter) {
        centroids.resize(k);
    }
    
    void addPoint(double x, double y) {
        points.push_back(Point(x, y));
    }
    
    void initializeCentroids() {
        // K-means++ initialization for better results
        random_device rd;
        mt19937 gen(rd());
        
        if (points.empty()) return;
        
        // Choose first centroid randomly
        uniform_int_distribution<> dis(0, points.size() - 1);
        centroids[0] = points[dis(gen)];
        
        // Choose remaining centroids
        for (int i = 1; i < k; i++) {
            vector<double> distances(points.size());
            double totalDistance = 0;
            
            // Calculate distances to nearest centroid
            for (int j = 0; j < points.size(); j++) {
                double minDist = INFINITY;
                for (int c = 0; c < i; c++) {
                    minDist = min(minDist, points[j].distanceTo(centroids[c]));
                }
                distances[j] = minDist * minDist;
                totalDistance += distances[j];
            }
            
            // Choose next centroid with probability proportional to squared distance
            uniform_real_distribution<> realDis(0, totalDistance);
            double target = realDis(gen);
            double cumulative = 0;
            
            for (int j = 0; j < points.size(); j++) {
                cumulative += distances[j];
                if (cumulative >= target) {
                    centroids[i] = points[j];
                    break;
                }
            }
        }
    }
    
    bool assignPointsToClusters() {
        bool changed = false;
        
        for (auto& point : points) {
            int bestCluster = 0;
            double minDistance = point.distanceTo(centroids[0]);
            
            for (int i = 1; i < k; i++) {
                double distance = point.distanceTo(centroids[i]);
                if (distance < minDistance) {
                    minDistance = distance;
                    bestCluster = i;
                }
            }
            
            if (point.cluster != bestCluster) {
                point.cluster = bestCluster;
                changed = true;
            }
        }
        
        return changed;
    }
    
    void updateCentroids() {
        vector<double> sumX(k, 0), sumY(k, 0);
        vector<int> count(k, 0);
        
        for (const auto& point : points) {
            if (point.cluster >= 0 && point.cluster < k) {
                sumX[point.cluster] += point.x;
                sumY[point.cluster] += point.y;
                count[point.cluster]++;
            }
        }
        
        for (int i = 0; i < k; i++) {
            if (count[i] > 0) {
                centroids[i].x = sumX[i] / count[i];
                centroids[i].y = sumY[i] / count[i];
            }
        }
    }
    
    void cluster() {
        initializeCentroids();
        
        for (int iter = 0; iter < maxIterations; iter++) {
            bool changed = assignPointsToClusters();
            updateCentroids();
            
            if (!changed) {
                cout << "Converged after " << (iter + 1) << " iterations" << endl;
                break;
            }
        }
    }
    
    vector<Point> getCentroids() const {
        return centroids;
    }
    
    vector<int> getClusterAssignments() const {
        vector<int> assignments;
        for (const auto& point : points) {
            assignments.push_back(point.cluster);
        }
        return assignments;
    }
    
    // Tính Within-Cluster Sum of Squares (WCSS)
    double calculateWCSS() const {
        double wcss = 0;
        
        for (const auto& point : points) {
            if (point.cluster >= 0 && point.cluster < k) {
                wcss += point.distanceTo(centroids[point.cluster]) * 
                       point.distanceTo(centroids[point.cluster]);
            }
        }
        
        return wcss;
    }
    
    // Tính Silhouette Score
    double calculateSilhouetteScore() const {
        if (points.size() <= 1 || k <= 1) return 0;
        
        double totalScore = 0;
        int validPoints = 0;
        
        for (int i = 0; i < points.size(); i++) {
            const Point& point = points[i];
            if (point.cluster < 0) continue;
            
            // Calculate a(i) - average distance to points in same cluster
            double a = 0;
            int sameClusterCount = 0;
            
            for (int j = 0; j < points.size(); j++) {
                if (i != j && points[j].cluster == point.cluster) {
                    a += point.distanceTo(points[j]);
                    sameClusterCount++;
                }
            }
            
            if (sameClusterCount > 0) {
                a /= sameClusterCount;
            }
            
            // Calculate b(i) - minimum average distance to points in other clusters
            double b = INFINITY;
            
            for (int cluster = 0; cluster < k; cluster++) {
                if (cluster == point.cluster) continue;
                
                double avgDist = 0;
                int otherClusterCount = 0;
                
                for (int j = 0; j < points.size(); j++) {
                    if (points[j].cluster == cluster) {
                        avgDist += point.distanceTo(points[j]);
                        otherClusterCount++;
                    }
                }
                
                if (otherClusterCount > 0) {
                    avgDist /= otherClusterCount;
                    b = min(b, avgDist);
                }
            }
            
            // Calculate silhouette score for this point
            if (b != INFINITY && max(a, b) > 0) {
                totalScore += (b - a) / max(a, b);
                validPoints++;
            }
        }
        
        return validPoints > 0 ? totalScore / validPoints : 0;
    }
    
    // Debug function để hiển thị quá trình clustering
    void debugClustering() {
        cout << "=== DEBUG K-MEANS CLUSTERING ===" << endl;
        cout << "Number of points: " << points.size() << endl;
        cout << "Number of clusters: " << k << endl;
        
        cout << "\nInitial centroids:" << endl;
        for (int i = 0; i < k; i++) {
            cout << "Centroid " << i << ": (" << fixed << setprecision(2) 
                 << centroids[i].x << ", " << centroids[i].y << ")" << endl;
        }
        
        // Run clustering with debug info
        initializeCentroids();
        
        for (int iter = 0; iter < min(5, maxIterations); iter++) {
            cout << "\nIteration " << (iter + 1) << ":" << endl;
            
            bool changed = assignPointsToClusters();
            
            // Show cluster assignments
            vector<int> clusterSizes(k, 0);
            for (const auto& point : points) {
                if (point.cluster >= 0 && point.cluster < k) {
                    clusterSizes[point.cluster]++;
                }
            }
            
            cout << "Cluster sizes: ";
            for (int i = 0; i < k; i++) {
                cout << clusterSizes[i] << " ";
            }
            cout << endl;
            
            updateCentroids();
            
            cout << "New centroids:" << endl;
            for (int i = 0; i < k; i++) {
                cout << "Centroid " << i << ": (" << fixed << setprecision(2) 
                     << centroids[i].x << ", " << centroids[i].y << ")" << endl;
            }
            
            cout << "WCSS: " << fixed << setprecision(2) << calculateWCSS() << endl;
            
            if (!changed) {
                cout << "Converged!" << endl;
                break;
            }
        }
        
        cout << "\nFinal Silhouette Score: " << fixed << setprecision(4) 
             << calculateSilhouetteScore() << endl;
        
        cout << "===============================" << endl;
    }
    
    // Elbow method để tìm k tối ưu
    static void elbowMethod(const vector<Point>& data, int maxK = 10) {
        cout << "\n=== ELBOW METHOD FOR OPTIMAL K ===" << endl;
        
        for (int testK = 1; testK <= maxK; testK++) {
            KMeansClustering kmeans(testK);
            
            for (const auto& point : data) {
                kmeans.addPoint(point.x, point.y);
            }
            
            kmeans.cluster();
            double wcss = kmeans.calculateWCSS();
            
            cout << "k=" << testK << ", WCSS=" << fixed << setprecision(2) << wcss << endl;
        }
        
        cout << "Look for the 'elbow' in the WCSS curve to find optimal k" << endl;
        cout << "===================================" << endl;
    }
};

// Linear Regression class
class LinearRegression {
private:
    double slope, intercept;
    vector<pair<double, double>> data;
    
public:
    void addDataPoint(double x, double y) {
        data.push_back({x, y});
    }
    
    void train() {
        if (data.size() < 2) return;
        
        double sumX = 0, sumY = 0, sumXY = 0, sumX2 = 0;
        int n = data.size();
        
        for (const auto& point : data) {
            sumX += point.first;
            sumY += point.second;
            sumXY += point.first * point.second;
            sumX2 += point.first * point.first;
        }
        
        slope = (n * sumXY - sumX * sumY) / (n * sumX2 - sumX * sumX);
        intercept = (sumY - slope * sumX) / n;
    }
    
    double predict(double x) const {
        return slope * x + intercept;
    }
    
    double getSlope() const { return slope; }
    double getIntercept() const { return intercept; }
    
    double calculateR2() const {
        if (data.empty()) return 0;
        
        double meanY = 0;
        for (const auto& point : data) {
            meanY += point.second;
        }
        meanY /= data.size();
        
        double ssRes = 0, ssTot = 0;
        for (const auto& point : data) {
            double predicted = predict(point.first);
            ssRes += (point.second - predicted) * (point.second - predicted);
            ssTot += (point.second - meanY) * (point.second - meanY);
        }
        
        return 1 - (ssRes / ssTot);
    }
};

// Hàm so sánh với random clustering
void compareWithRandomClustering(const vector<Point>& data, int k) {
    cout << "\n=== COMPARISON WITH RANDOM CLUSTERING ===" << endl;
    
    // Random clustering
    vector<Point> randomData = data;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, k - 1);
    
    for (auto& point : randomData) {
        point.cluster = dis(gen);
    }
    
    // Calculate WCSS for random clustering
    vector<Point> randomCentroids(k);
    vector<double> sumX(k, 0), sumY(k, 0);
    vector<int> count(k, 0);
    
    for (const auto& point : randomData) {
        sumX[point.cluster] += point.x;
        sumY[point.cluster] += point.y;
        count[point.cluster]++;
    }
    
    for (int i = 0; i < k; i++) {
        if (count[i] > 0) {
            randomCentroids[i].x = sumX[i] / count[i];
            randomCentroids[i].y = sumY[i] / count[i];
        }
    }
    
    double randomWCSS = 0;
    for (const auto& point : randomData) {
        randomWCSS += point.distanceTo(randomCentroids[point.cluster]) * 
                     point.distanceTo(randomCentroids[point.cluster]);
    }
    
    cout << "Random clustering WCSS: " << fixed << setprecision(2) << randomWCSS << endl;
    cout << "K-means finds much better clusters by minimizing WCSS!" << endl;
    cout << "=========================================" << endl;
}

int main() {
    int n, k;
    cin >> n >> k;
    
    KMeansClustering kmeans(k);
    vector<Point> inputData;
    
    for (int i = 0; i < n; i++) {
        double x, y;
        cin >> x >> y;
        kmeans.addPoint(x, y);
        inputData.push_back(Point(x, y));
    }
    
    kmeans.cluster();
    
    auto centroids = kmeans.getCentroids();
    auto assignments = kmeans.getClusterAssignments();
    
    // Output centroids
    for (const auto& centroid : centroids) {
        cout << fixed << setprecision(2) << centroid.x << " " << centroid.y << endl;
    }
    
    // Output assignments
    for (int assignment : assignments) {
        cout << assignment << endl;
    }
    
    // Uncomment để xem debug info:
    // kmeans.debugClustering();
    
    // Test elbow method:
    // KMeansClustering::elbowMethod(inputData, 8);
    
    // Compare with random clustering:
    // compareWithRandomClustering(inputData, k);
    
    // Test linear regression:
    // LinearRegression lr;
    // for (const auto& point : inputData) {
    //     lr.addDataPoint(point.x, point.y);
    // }
    // lr.train();
    // cout << "Linear regression: y = " << lr.getSlope() << "x + " << lr.getIntercept() << endl;
    // cout << "R² = " << lr.calculateR2() << endl;
    
    return 0;
}