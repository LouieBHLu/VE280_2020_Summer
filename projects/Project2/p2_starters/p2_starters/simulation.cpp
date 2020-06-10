/*
 * This is VE280 Project 2, SU2020.
 * Written by Ziqiao Ma and Zhuoer Zhu.
 * Latest Update: 5/29/2020.
 * All rights reserved.
 */

#include "simulation.h"

// TODO: Define your functions in this header file.
void trending(string line, User_t user[], Tag_t tag[], int order, int n){
                cout << ">> trending" << endl;
            int top_n;//top nth tag
            string number;
            while(line[order+9]){
                number = number + line[order+9];
                order++; 
            }
            top_n = atoi(number.c_str()); 
            //read all users' all posts' all tags
            int current_tag_number = 0;
            //get current tag number
            for(int j = 1; j <= n-1; j++){//every user
                if(user[j].num_posts > 0){
                    for(unsigned int i = 1; i <= user[j].num_posts; i++){//every post
                        current_tag_number += user[j].posts[i-1].num_tags;
                    }
                }
            }
            //get current none-empty struct tag number
            int current_tag_struct_num = 0;
            while(1){
                if(!tag[current_tag_struct_num].tag_content.empty()){
                    current_tag_struct_num++;
                }
                else break;
            }

            for(int j = 1; j <= n-1; j++){//every user
                if(user[j].num_posts > 0){
                    for(unsigned int i = 1; i <= user[j].num_posts; i++){//every post
                        for(unsigned int k = 0; k < user[j].posts[i-1].num_tags; k++){
                            int nth = 0;
                            while(nth < current_tag_struct_num){
                                if(user[j].posts[i-1].tags[k] == tag[nth].tag_content) break;
                                else nth++;
                            }
                            if(nth == current_tag_struct_num){//if the tag is new!
                                tag[current_tag_struct_num].tag_content = user[j].posts[i-1].tags[k];
                                tag[current_tag_struct_num].tag_score = 5 + user[j].posts[i-1].num_likes + user[j].posts[i-1].num_comments*3;
                                current_tag_struct_num++;
                            }
                            else{// if the tag is not new
                                tag[nth].tag_score = tag[nth].tag_score + 5 + user[j].posts[i-1].num_likes + user[j].posts[i-1].num_comments*3;
                            }
                        }
                    }
                }
            }
            //rank the tags and post!
    for(int i = 0; i < current_tag_struct_num - 1; i++) {
        for(int j = 0; j < current_tag_struct_num - 1 - i; j++) {
            if(tag[j].tag_score < tag[j+1].tag_score) {
                // switch two tag structs
                int temp_score = tag[j+1].tag_score;
                tag[j+1].tag_score = tag[j].tag_score;
                tag[j].tag_score = temp_score;
                //switch two tag content
                string temp_content = tag[j+1].tag_content;
                tag[j+1].tag_content = tag[j].tag_content;
                tag[j].tag_content = temp_content;
            }
        }
    }
        //rank the tags with the same score
    for(int i = 0; i < current_tag_struct_num - 1; i++) {
        for(int j = 0; j < current_tag_struct_num - 1 - i; j++) {
            if(tag[j].tag_score == tag[j+1].tag_score){
            int k = 0;
            int small_size;
            int switch_po = 0;
            if(tag[j].tag_content.size() <= tag[j+1].tag_content.size()){
                small_size = tag[j].tag_content.size();
            }
            else{
                small_size =tag[j+1].tag_content.size();
            } 
            while(k < small_size){
                if(tag[j].tag_content[k] == tag[j+1].tag_content[k]){
                    k++;
                }
                else if(tag[j].tag_content[k] < tag[j+1].tag_content[k]){
                    break;
                }
                else{
                    switch_po = 1;
                    break;
                }
            }
            if(switch_po){
                //switch two tag content
                string temp_content = tag[j+1].tag_content;
                tag[j+1].tag_content = tag[j].tag_content;
                tag[j].tag_content = temp_content;
            }
            }
        }
    }
    //assign reference to tags
    if(top_n > current_tag_struct_num){// top is more than current tag struct number
        for(int i = 0; i < current_tag_struct_num; i++){
            // const Tag_t &r_tag = tag[i];
            // printTag(r_tag, i+1);
            //printTag(tag[i],i+1);
            cout << i+1 << " " << tag[i].tag_content << ": " << tag[i].tag_score << endl;
        }
    }
    else{
        for(int i = 0; i < top_n; i++){
            // const Tag_t &r_tag = tag[i];
            // printTag(r_tag, i+1);
            //printTag(tag[i],i+1);
            cout << i+1 << " " << tag[i].tag_content << ": " << tag[i].tag_score << endl;
        }
    }
    //clear all tag score to 0 and clear tag content
    for(int i = 0; i < current_tag_struct_num; i++){
        tag[i].tag_score = 0;
        tag[i].tag_content = "";
    }
}
void visit(int position_visit, string line, User_t user[]){
                cout << ">> visit" << endl;
            string user1name;
            string user2name;
            //get the name of two users
            for(int i = 0; i < position_visit - 1; i++){
                user1name = user1name + line[i];
            }
            int j = position_visit + 6;
            while(line[j]){
                user2name = user2name + line[j];
                j++;
            }
            //figure out the relationship
            int user1_order = 1; int user2_order = 1;
            string relationship;
            int one_following_two = 0; int two_following_one = 0; 
            int following_himself = 0;
            while(1){//get the order of first users
                if(user[user1_order].username == user1name) break;
                else user1_order++;
            }
            while(1){//get the order of second users
                if(user[user2_order].username == user2name) break;
                else user2_order++;
            }
            if(user[user1_order].num_following > 0){// check the first user
                for(unsigned int i = 0; i < user[user1_order].num_following; i++){
                    if(user[user1_order].following[i]->username == user[user1_order].username){
                        following_himself = 1;
                    }
                    else if(user[user1_order].following[i]->username == user[user2_order].username){
                        one_following_two = 1;
                    }
                }
            }
            if(user[user2_order].num_following > 0){// check the second user
                for(unsigned int i = 0; i < user[user2_order].num_following; i++){
                    if(user[user2_order].following[i]->username == user[user1_order].username){
                        two_following_one = 1;
                    }
                }
            }
            //decide relationship
            if(following_himself == 1) relationship = "";
            else if(one_following_two == 1 && two_following_one == 1) relationship = "friend";
            else if(one_following_two == 1 && two_following_one == 0) relationship = "following";
            else if(one_following_two == 0) relationship = "stranger";
            //print
            cout << user[user2_order].username << endl;
            cout << relationship << endl;
            cout << "Followers: " << user[user2_order].num_followers
            << "\nFollowing: " << user[user2_order].num_following << endl;
}
void follow(int position_follow, string line, User_t user[]){
                cout << ">> follow" << endl;
            string user1name;
            string user2name;
            //get the name of two users
            for(int i = 0; i < position_follow - 1; i++){
                user1name = user1name + line[i];
            }
            int j = position_follow + 7;
            while(line[j]){
                user2name = user2name + line[j];
                j++;
            }
            // get orders of two users
            int user1_order = 1; int user2_order = 1;
            while(1){//get the order of first users
                if(user[user1_order].username == user1name) break;
                else user1_order++;
            }
            while(1){//get the order of second users
                if(user[user2_order].username == user2name) break;
                else user2_order++;
            }
            //be each other's follower and following
            user[user2_order].follower[user[user2_order].num_followers] = &user[user1_order];
            user[user1_order].following[user[user1_order].num_following] = &user[user2_order];
            user[user2_order].num_followers++;
            user[user1_order].num_following++;
}
void refresh(int position_refresh, string line, User_t user[]){
                cout << ">> refresh" << endl;
            string user1name;
            //cout << line.size() << endl;
            //read the name of user1
            for(int i = 0; i < position_refresh - 1; i++){
                user1name = user1name + line[i];
            }
            //get the order of the user
            int user1_order = 1;
            while(1){//get the order of first users
                if(user[user1_order].username == user1name) break;
                else user1_order++;
            }
            //print user1's own postsz
            if(user[user1_order].num_posts > 0){
            for(unsigned int i = 0; i < user[user1_order].num_posts; i++){
                cout << user[user1_order].posts[i].owner->username << endl;
                cout << user[user1_order].posts[i].title << endl;
                cout << user[user1_order].posts[i].text << endl;
                cout << "Tags: ";
                for(unsigned int k = 0; k < user[user1_order].posts[i].num_tags; ++k){
                    cout << user[user1_order].posts[i].tags[k] << " ";
                }
                cout << "\nLikes: " << user[user1_order].posts[i].num_likes << endl;
                if (user[user1_order].posts[i].num_comments > 0){
                    cout << "Comments:" << endl;
                    for(unsigned int k = 0; k<user[user1_order].posts[i].num_comments; ++k){
                        cout << user[user1_order].posts[i].comments[k].user->username << ": "
                                << user[user1_order].posts[i].comments[k].text << endl;
                    }
                }
                cout << "- - - - - - - - - - - - - - -" << endl;
                //printPost(user[user1_order].posts[i]);
            }
            }

            //print following's posts
            if(user[user1_order].num_following > 0){
                for(unsigned int i = 0; i < user[user1_order].num_following; i++){
                    if(user[user1_order].following[i]->num_posts > 0){
                        for(unsigned int j = 0; j < user[user1_order].following[i]->num_posts; j++){
                cout << user[user1_order].following[i]->posts[j].owner->username << endl;
                cout << user[user1_order].following[i]->posts[j].title << endl;
                cout << user[user1_order].following[i]->posts[j].text << endl;
                cout << "Tags: ";
                for(unsigned int k = 0; k < user[user1_order].following[i]->posts[j].num_tags; ++k){
                    cout << user[user1_order].following[i]->posts[j].tags[k] << " ";
                }
                cout << "\nLikes: " << user[user1_order].following[i]->posts[j].num_likes << endl;
                if (user[user1_order].following[i]->posts[j].num_comments > 0){
                    cout << "Comments:" << endl;
                    for(unsigned int k = 0; k<user[user1_order].following[i]->posts[j].num_comments; ++k){
                        cout << user[user1_order].following[i]->posts[j].comments[k].user->username << ": "
                                << user[user1_order].following[i]->posts[j].comments[k].text << endl;
                    }
                }
                cout << "- - - - - - - - - - - - - - -" << endl;

                    //printPost(user[user1_order].following[i]->posts[j]);  
                        }
                    }
                }
            }
}
void post(int position_post, string line, User_t user[], int *line_num, string logname){
            cout << ">> post" << endl;
            string user1name;
            ifstream log;
            log.open(logname);

            for(int i = 0; i < *line_num; i++){
                getline(log,line);
            }
            //read the name of user1
            for(int i = 0; i < position_post - 1; i++){
                user1name = user1name + line[i];
            }
            //get the order of the user
            int user1_order = 1;
            while(1){//get the order of first users
                if(user[user1_order].username == user1name) break;
                else user1_order++;
            }
            //assign the owner of the post to the user
            user[user1_order].posts[user[user1_order].num_posts].owner = &user[user1_order];
            
            //get title
            getline(log,line);
            (*line_num)++;
            user[user1_order].posts[user[user1_order].num_posts].title = line;
            //get tags
            int t = 0;
            while(1){
                getline(log,line);
                (*line_num)++;
                if(line[0] == '#' && line[line.size()-1] == '#'){
                    int size = line.size()-1;
                    for(int k = 1; k < size; k++){
                        user[user1_order].posts[user[user1_order].num_posts].tags[t] = user[user1_order].posts[user[user1_order].num_posts].tags[t] + line[k];
                    }
                    t++;
                }
                else break;
            }
            user[user1_order].posts[user[user1_order].num_posts].num_tags = t;//jth user's ith post's tag number;
            //read the text
            user[user1_order].posts[user[user1_order].num_posts].text = line;
            //initialize likes and comments
            user[user1_order].posts[user[user1_order].num_posts].num_likes = 0;
            user[user1_order].posts[user[user1_order].num_posts].num_comments = 0;
            //add post numbers
            user[user1_order].num_posts++;

            log.close();
}
void like(User_t user[],int user2_order, int user1_order, int like_post_num){
            //if no exception
            user[user2_order].posts[like_post_num-1].like_users[user[user2_order].posts[like_post_num-1].num_likes] = &user[user1_order];
            user[user2_order].posts[like_post_num-1].num_likes++;
}
void comment(string line, User_t user[],int *line_num, string logname, int user2_order, int user1_order, int comment_post_num){
        //read the comment
        ifstream log;
        log.open(logname);
        getline(log,line);
        (*line_num)++;
        user[user2_order].posts[comment_post_num-1].comments[user[user2_order].posts[comment_post_num-1].num_comments].text = line;
        user[user2_order].posts[comment_post_num-1].comments[user[user2_order].posts[comment_post_num-1].num_comments].user = &user[user1_order];
        user[user2_order].posts[comment_post_num-1].num_comments++;
        log.close();
}

/* Helper Functions */

// Printing

void printUser(User_t& user, const string& relationship){
    cout << user.username << endl;
    cout << relationship << endl;
    cout << "Followers: " << user.num_followers
         << "\nFollowing: " << user.num_following << endl;
}


void printPost(Post_t& post){
    cout << post.owner->username << endl;
    cout << post.title << endl;
    cout << post.text << endl;
    cout << "Tags: ";
    for(unsigned int i = 0; i<post.num_tags; ++i){
        cout << post.tags[i] << " ";
    }
    cout << "\nLikes: " << post.num_likes << endl;
    if (post.num_comments > 0){
        cout << "Comments:" << endl;
        for(unsigned int i = 0; i<post.num_comments; ++i){
            cout << post.comments[i].user->username << ": "
                 << post.comments[i].text << endl;
        }
    }
    cout << "- - - - - - - - - - - - - - -" << endl;
}


void printTag(const Tag_t& tag, unsigned int rank){
    cout << rank << " " << tag.tag_content << ": " << tag.tag_score << endl;
}
