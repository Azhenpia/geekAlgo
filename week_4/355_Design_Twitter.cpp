struct status{
    int timeStamp;
    int twiId;
    list<pair<int, int>>::iterator curr;
    list<pair<int, int>>::iterator end;
    status(int ts, int id, list<pair<int, int>>::iterator c, list<pair<int, int>>::iterator e) : 
    timeStamp(ts), twiId(id), curr(c), end(e) {}
};

class Twitter {
public:
    struct user_info{
        unordered_set<int> followee;
        list<pair<int, int>> post;
    };

    unordered_map<int, user_info> users;
    int timeStamp;

    Twitter() {
        timeStamp = 0;
    }
    
    void postTweet(int userId, int tweetId) {
        users[userId].post.push_front({timeStamp++, tweetId});
    }
    
    vector<int> getNewsFeed(int userId) {
        vector<int> ans;
        vector<int> target_user(users[userId].followee.begin(), users[userId].followee.end());
        target_user.push_back(userId);
        auto comp = [](status & a, status & b){
            return a.timeStamp < b.timeStamp;
        };
        priority_queue<status, vector<status>, decltype(comp)> q(comp);
        for(auto & u: target_user){
            if(!users[u].post.empty())
                q.push(status(users[u].post.begin()->first, 
                            users[u].post.begin()->second, 
                            users[u].post.begin(), 
                            users[u].post.end()));
        }
        while(!q.empty() && ans.size() < 10){
            auto p = q.top(); q.pop();
            ans.push_back(p.twiId);
            auto itr = ++p.curr;
            if(p.curr != p.end)
                q.push(status(itr->first, itr->second, itr, p.end));
        }
        return ans;
    }
    
    void follow(int followerId, int followeeId) {
        users[followerId].followee.insert(followeeId);
    }
    
    void unfollow(int followerId, int followeeId) {
        users[followerId].followee.erase(followeeId);
    }
};

/**
 * Your Twitter object will be instantiated and called as such:
 * Twitter* obj = new Twitter();
 * obj->postTweet(userId,tweetId);
 * vector<int> param_2 = obj->getNewsFeed(userId);
 * obj->follow(followerId,followeeId);
 * obj->unfollow(followerId,followeeId);
 */