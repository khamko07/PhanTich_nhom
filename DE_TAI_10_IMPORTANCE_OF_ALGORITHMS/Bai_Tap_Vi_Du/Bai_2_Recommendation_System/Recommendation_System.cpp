#include <iostream>
#include <vector>
#include <map>
#include <cmath>
#include <algorithm>
using namespace std;

class RecommendationSystem {
private:
    vector<vector<int>> ratings; // user x movie ratings
    int numUsers, numMovies;
    
public:
    RecommendationSystem(int users, int movies) : numUsers(users), numMovies(movies) {
        ratings.resize(users, vector<int>(movies, 0));
    }
    
    void setRating(int user, int movie, int rating) {
        ratings[user][movie] = rating;
    }
    
    double calculateSimilarity(int user1, int user2) {
        double dotProduct = 0, norm1 = 0, norm2 = 0;
        int commonMovies = 0;
        
        for (int movie = 0; movie < numMovies; movie++) {
            if (ratings[user1][movie] > 0 && ratings[user2][movie] > 0) {
                dotProduct += ratings[user1][movie] * ratings[user2][movie];
                norm1 += ratings[user1][movie] * ratings[user1][movie];
                norm2 += ratings[user2][movie] * ratings[user2][movie];
                commonMovies++;
            }
        }
        
        if (commonMovies == 0 || norm1 == 0 || norm2 == 0) return 0;
        
        // Cosine similarity
        return dotProduct / (sqrt(norm1) * sqrt(norm2));
    }
    
    vector<int> recommendMovies(int targetUser, int numRecommendations) {
        // Find similar users
        vector<pair<double, int>> similarities;
        
        for (int user = 0; user < numUsers; user++) {
            if (user != targetUser) {
                double similarity = calculateSimilarity(targetUser, user);
                if (similarity > 0) {
                    similarities.push_back({similarity, user});
                }
            }
        }
        
        // Sort by similarity (descending)
        sort(similarities.rbegin(), similarities.rend());
        
        // Generate recommendations
        map<int, double> movieScores;
        
        // Use top similar users for recommendations
        int maxSimilarUsers = min(5, (int)similarities.size());
        
        for (int i = 0; i < maxSimilarUsers; i++) {
            int similarUser = similarities[i].second;
            double similarity = similarities[i].first;
            
            for (int movie = 0; movie < numMovies; movie++) {
                // Recommend movies that target user hasn't seen
                if (ratings[targetUser][movie] == 0 && ratings[similarUser][movie] > 0) {
                    movieScores[movie] += similarity * ratings[similarUser][movie];
                }
            }
        }
        
        // Sort recommendations by score
        vector<pair<double, int>> recommendations;
        for (auto& [movie, score] : movieScores) {
            recommendations.push_back({score, movie});
        }
        
        sort(recommendations.rbegin(), recommendations.rend());
        
        // Return top recommendations
        vector<int> result;
        for (int i = 0; i < min(numRecommendations, (int)recommendations.size()); i++) {
            result.push_back(recommendations[i].second);
        }
        
        return result;
    }
    
    // Debug function để hiển thị quá trình tính toán
    void debugRecommendation(int targetUser, int numRecommendations) {
        cout << "=== DEBUG RECOMMENDATION SYSTEM ===" << endl;
        cout << "Target user: " << targetUser << endl;
        
        // Show target user's ratings
        cout << "Target user's ratings: ";
        for (int movie = 0; movie < numMovies; movie++) {
            cout << ratings[targetUser][movie] << " ";
        }
        cout << endl;
        
        // Calculate and show similarities
        cout << "\nUser similarities:" << endl;
        vector<pair<double, int>> similarities;
        
        for (int user = 0; user < numUsers; user++) {
            if (user != targetUser) {
                double similarity = calculateSimilarity(targetUser, user);
                similarities.push_back({similarity, user});
                cout << "User " << user << ": " << fixed << setprecision(4) 
                     << similarity << endl;
            }
        }
        
        sort(similarities.rbegin(), similarities.rend());
        
        cout << "\nTop similar users:" << endl;
        int maxShow = min(3, (int)similarities.size());
        for (int i = 0; i < maxShow; i++) {
            int user = similarities[i].second;
            cout << "User " << user << " (similarity: " 
                 << similarities[i].first << "): ";
            for (int movie = 0; movie < numMovies; movie++) {
                cout << ratings[user][movie] << " ";
            }
            cout << endl;
        }
        
        // Show recommendation calculation
        cout << "\nRecommendation scores:" << endl;
        map<int, double> movieScores;
        
        for (int i = 0; i < min(3, (int)similarities.size()); i++) {
            int similarUser = similarities[i].second;
            double similarity = similarities[i].first;
            
            for (int movie = 0; movie < numMovies; movie++) {
                if (ratings[targetUser][movie] == 0 && ratings[similarUser][movie] > 0) {
                    movieScores[movie] += similarity * ratings[similarUser][movie];
                }
            }
        }
        
        for (auto& [movie, score] : movieScores) {
            cout << "Movie " << movie << ": " << score << endl;
        }
        
        cout << "===================================" << endl;
    }
    
    // Hàm phân tích chất lượng recommendation
    void analyzeRecommendationQuality(int targetUser) {
        cout << "\n=== RECOMMENDATION QUALITY ANALYSIS ===" << endl;
        
        // Tính độ đa dạng của recommendations
        vector<int> recommendations = recommendMovies(targetUser, numMovies);
        
        cout << "Number of possible recommendations: " << recommendations.size() << endl;
        
        // Tính coverage (bao nhiêu % phim có thể được recommend)
        int unwatchedMovies = 0;
        for (int movie = 0; movie < numMovies; movie++) {
            if (ratings[targetUser][movie] == 0) {
                unwatchedMovies++;
            }
        }
        
        double coverage = (double)recommendations.size() / unwatchedMovies * 100;
        cout << "Coverage: " << fixed << setprecision(2) << coverage << "%" << endl;
        
        // Phân tích độ tin cậy dựa trên số lượng user tương tự
        int similarUsers = 0;
        for (int user = 0; user < numUsers; user++) {
            if (user != targetUser && calculateSimilarity(targetUser, user) > 0.1) {
                similarUsers++;
            }
        }
        
        cout << "Number of similar users (similarity > 0.1): " << similarUsers << endl;
        cout << "Confidence level: " << (similarUsers >= 3 ? "High" : 
                                        similarUsers >= 1 ? "Medium" : "Low") << endl;
        
        cout << "========================================" << endl;
    }
};

// Hàm so sánh với popularity-based recommendation
void compareWithPopularityBased(const vector<vector<int>>& ratings, int targetUser) {
    cout << "\n=== COMPARISON WITH POPULARITY-BASED ===" << endl;
    
    int numUsers = ratings.size();
    int numMovies = ratings[0].size();
    
    // Tính popularity score cho mỗi phim
    vector<pair<double, int>> popularity;
    
    for (int movie = 0; movie < numMovies; movie++) {
        double totalRating = 0;
        int ratingCount = 0;
        
        for (int user = 0; user < numUsers; user++) {
            if (ratings[user][movie] > 0) {
                totalRating += ratings[user][movie];
                ratingCount++;
            }
        }
        
        if (ratingCount > 0 && ratings[targetUser][movie] == 0) {
            double avgRating = totalRating / ratingCount;
            popularity.push_back({avgRating, movie});
        }
    }
    
    sort(popularity.rbegin(), popularity.rend());
    
    cout << "Top popular movies (that target user hasn't seen):" << endl;
    for (int i = 0; i < min(3, (int)popularity.size()); i++) {
        cout << "Movie " << popularity[i].second 
             << " (avg rating: " << popularity[i].first << ")" << endl;
    }
    
    cout << "Collaborative filtering provides personalized recommendations!" << endl;
    cout << "===========================================" << endl;
}

int main() {
    int n, m, target;
    cin >> n >> m >> target;
    
    RecommendationSystem rs(n, m);
    
    for (int user = 0; user < n; user++) {
        for (int movie = 0; movie < m; movie++) {
            int rating;
            cin >> rating;
            rs.setRating(user, movie, rating);
        }
    }
    
    int numRecommendations;
    cin >> numRecommendations;
    
    vector<int> recommendations = rs.recommendMovies(target, numRecommendations);
    
    for (int movie : recommendations) {
        cout << movie << " ";
    }
    cout << endl;
    
    // Uncomment để xem debug info:
    // rs.debugRecommendation(target, numRecommendations);
    // rs.analyzeRecommendationQuality(target);
    
    return 0;
}