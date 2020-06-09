#include "simulation.h"

int main(int argc, char const *argv[])
{
    // check arguments number
	// try{
	// if(argc < 3){
	// ostringstream oStream;
	// oStream << "Error: Wrong number of arguments!" << endl;
	// oStream <<  "Usage: ./p2 <username> <logfile>" << endl;
	// throw Exception_t(INVALID_ARGUMENT, oStream.str());
	//     }
    // }
    // catch (Exception_t &exception){
    // cout << exception.error_info;
	// return 0;
    // }

	//read the arguments
    // string name = argv[1];
    // string logname = argv[2];
    string name = "username";
    //string name = "usernameexp";
    string logname = "logfile";
    //open file username
	ifstream iFile;
    iFile.open(name);
	//check whether open successfully
	try{
		if(!iFile){
		ostringstream oStream;
		oStream << "Error: Cannot open file " << name << "!" << endl;
		throw Exception_t(FILE_MISSING, oStream.str());
	    }
    }
    catch (Exception_t &exception){
    	cout << exception.error_info;
		return 0;
    }
    
    //create max number of struct tag_t
    Tag_t tag[5000];
    for(int i = 0; i < 5000; i++){
        tag[i].tag_score = 0;
    }
	//read the name of users
	User_t user[MAX_USERS + 1];
	int n = 0;//number of users read
    if (iFile){
        string line;
        while(getline(iFile, line)) {
            user[n].username = line;
            n++;
            if(n > 20) break;
        }
        iFile.close();
    }
    iFile.close();
        try{
            if(n > 20){
                ostringstream oStream;
		        oStream << "Error: Too many users! " << endl;
                oStream << "Maximal number of users is " << MAX_USERS << "." << endl;
		        throw Exception_t(CAPACITY_OVERFLOW, oStream.str()); 
            }
		
        }      
        catch (Exception_t &exception){
    	    cout << exception.error_info;
		    return 0;
        }
    

	//open and read user_info
    ifstream userinfor;
    //ckech exception missing file
    int wrong_number = 0;
    for(int k = 1; k <= n - 1; k++){
        string location = user[0].username+ "/" + user[k].username + "/user_info";
        userinfor.open(location);
		if(!userinfor){
            wrong_number = k;
		    break;
	    }
        userinfor.close();
    }
	try{
		if(wrong_number != 0){
		ostringstream oStream;
		oStream << "Error: Cannot open file" << endl;
        oStream << user[0].username << user[wrong_number].username << "/user_info!" << endl;
		throw Exception_t(FILE_MISSING, oStream.str());
	    }
    }
    catch (Exception_t &exception){
    	cout << exception.error_info;
		return 0;
    }

//open and read user_info
for(int k = 1; k <= n - 1; k++){
    string location = user[0].username+ "/" + user[k].username + "/user_info";
    userinfor.open(location);
    //post number
    unsigned int num;
    string line;
    getline(userinfor,line);
    num = atoi(line.c_str());
    try{
        if(num > MAX_POSTS){
            ostringstream oStream;
		    oStream << "Error: Too many posts for user " << user[k].username << "!" << endl;
            oStream << "Maximal number of posts is " << MAX_POSTS << "." << endl;
		    throw Exception_t(CAPACITY_OVERFLOW, oStream.str()); 
        }
		
    }      
    catch (Exception_t &exception){
    	cout << exception.error_info;
		return 0;
    }
    user[k].num_posts = num;
    //following number
    getline(userinfor,line);
    num = atoi(line.c_str());
    try{
        if(num > MAX_FOLLOWING){
            ostringstream oStream;
		    oStream << "Error: Too many followings for user " << user[k].username << "!" << endl;
            oStream << "Maximal number of followings is " << MAX_FOLLOWING << "." << endl;
		    throw Exception_t(CAPACITY_OVERFLOW, oStream.str()); 
        }
		
    }      
    catch (Exception_t &exception){
    	cout << exception.error_info;
		return 0;
    }
    user[k].num_following = num;
        //read following TODO:need exception exam
    for(unsigned int i = 0; i < num; i++){
        getline(userinfor,line);
        for(int j = 1; j <= n-1; j++){
            if(line == user[j].username){
                user[k].following[i] = &user[j];//point to another user
            }
        }
    }
    //follower number
    getline(userinfor,line);
    num = atoi(line.c_str());
    try{
        if(num > MAX_FOLLOWERS){
            ostringstream oStream;
		    oStream << "Error: Too many followers for user " << user[k].username << "!" << endl;
            oStream << "Maximal number of followers is " << MAX_FOLLOWERS << "." << endl;
		    throw Exception_t(CAPACITY_OVERFLOW, oStream.str()); 
        }
		
    }      
    catch (Exception_t &exception){
    	cout << exception.error_info;
		return 0;
    }
    user[k].num_followers = num;
        //read followers TODO:need exception exam
    for(unsigned int i = 0; i < num; i++){
        getline(userinfor,line);
        for(int j = 1; j <= n; j++){
            if(line == user[j].username){
                user[k].follower[i] = &user[j];
            }
        }
    }
    userinfor.close();    
    }

    //open and read posts
    ifstream postinfo;
    unsigned int number_tag[MAX_USERS + 1][MAX_POSTS] = {0};
    unsigned int number_likes[MAX_USERS + 1][MAX_POSTS] = {0};
    unsigned int number_comments[MAX_USERS + 1][MAX_POSTS] = {0};

    for(int j = 1; j <= n-1; j++){//every user
        if(user[j].num_posts > 0){
        for(unsigned int i = 1; i <= user[j].num_posts; i++){//every post
            int num_tag = 0;
            string lo_num = to_string(i);//post name
            //user[0].username+ "/" + user[k].username + "/user_info";
            string location = user[0].username+ "/" + user[j].username + "/posts/" + lo_num;
            postinfo.open(location);
            //get title
            string line;
            getline(postinfo,line);
            user[j].posts[i-1].title = line;
            //get tags number only
            while(1){
                getline(postinfo,line);
                if(line[0] == '#' && line[line.size()-1] == '#'){
                    num_tag++;                
                }
                else break;
            }
            number_tag[j][i-1] = num_tag;//jth user's ith post's tag number;
            //read the text
            user[j].posts[i-1].text = line;
            //read the likes number
            getline(postinfo,line);
            number_likes[j][i-1] = atoi(line.c_str());
            //skip the likes
            if(number_likes[j][i-1] != 0){
                for(unsigned int a = 0; a < number_likes[j][i-1]; a++) getline(postinfo,line);
            }
            //read the comments number
            getline(postinfo,line);
            number_comments[j][i-1] = atoi(line.c_str());
            postinfo.close();
        }        
        }
    }
    
    //examine the tag number TODO: find a counterexample!
    int flag_1 = 0;
    int wrong_user;
    int wrong_post;
        for(int i = 1; i <= n-1; i++){//each user tag number
            for(unsigned int j = 1; j <= user[i].num_posts; j++){//each post
                if(number_tag[i][j-1] > MAX_TAGS){
                    wrong_user = i;
                    wrong_post = j-1;
                    flag_1++;
                    break;
                }
            }
            if(flag_1 == 1) break;
        }    
    try{
        if(flag_1 == 1){
            ostringstream oStream;
		    oStream << "Error: Too many tags for post " << user[wrong_user].posts[wrong_post].title << "!" << endl;
            oStream << "Maximal number of tags is " << MAX_TAGS << "." << endl;
		    throw Exception_t(CAPACITY_OVERFLOW, oStream.str());
        }   
    }      
    catch (Exception_t &exception){
        cout << exception.error_info;
	    return 0;
    }
    flag_1 = 0;
        for(int i = 1; i <= n-1; i++){//each user  like number
            for(unsigned int j = 1; j <= user[i].num_posts; j++){//each post
                if(number_likes[i][j-1] > MAX_LIKES){
                    wrong_user = i;
                    wrong_post = j-1;
                    flag_1++;
                    break;
                }
            }
            if(flag_1 == 1) break;
        }

    try{
        if(flag_1 == 1){
            ostringstream oStream;
		    oStream << "Error: Too many likes for post " << user[wrong_user].posts[wrong_post].title << "!" << endl;
            oStream << "Maximal number of likes is " << MAX_LIKES << "." << endl;
		    throw Exception_t(CAPACITY_OVERFLOW, oStream.str());
        }
    }      
    catch (Exception_t &exception){
        cout << exception.error_info;
	    return 0;
    }

    flag_1 = 0;
        for(int i = 1; i <= n-1; i++){//each user comments number
            for(unsigned int j = 1; j <= user[i].num_posts; j++){//each post
                if(number_comments[i][j-1] > MAX_COMMENTS){
                    wrong_user = i;
                    wrong_post = j-1;
                    flag_1++;
                    break;
                }
            }
            if(flag_1 == 1) break;
        }
    try{
        if(flag_1 == 1){
            ostringstream oStream;
		    oStream << "Error: Too many comments for post " << user[wrong_user].posts[wrong_post].title << "!" << endl;
            oStream << "Maximal number of comments is " << MAX_COMMENTS << "." << endl;
		    throw Exception_t(CAPACITY_OVERFLOW, oStream.str());

        }
    }      
    catch (Exception_t &exception){
        cout << exception.error_info;
	    return 0;
    }


    
    //put the number into each post
    for(int j = 1; j <= n-1; j++){
        for(unsigned int i = 1; i <= user[j].num_posts; i++){
            user[j].posts[i-1].num_tags = number_tag[j][i-1];
            user[j].posts[i-1].num_likes = number_likes[j][i-1];
            user[j].posts[i-1].num_comments = number_comments[j][i-1];
        }
    }
    
    
    //read posts!
    for(int j = 1; j <= n-1; j++){//every user
        if(user[j].num_posts > 0){
            for(unsigned int i = 1; i <= user[j].num_posts; i++){//every post
            string lo_num = to_string(i);//post name
            string location = user[0].username+ "/" + user[j].username + "/posts/" + lo_num;
            postinfo.open(location);
            //get title
            string line;
            getline(postinfo,line);
            //read tags
            int t = 0;
            while(1){
                getline(postinfo,line);
                if(line[0] == '#' && line[line.size()-1] == '#'){
                    int size = line.size()-1;
                    for(int k = 1; k < size; k++){
                        user[j].posts[i-1].tags[t] = user[j].posts[i-1].tags[t] + line[k];
                    }
                    t++;  
                }
                else break;
            }
            //read text
            user[j].posts[i-1].text = line;
            //skip likes number and read number
            getline(postinfo,line);//skip likes number
            if(user[j].posts[i-1].num_likes > 0){//assign likes
                for(unsigned int k = 0; k < user[j].posts[i-1].num_likes; k++){
                    getline(postinfo,line);
                    for(int m = 1; m <= n; m++){
                        if(user[m].username == line){
                            user[j].posts[i-1].like_users[k] = &user[m];
                            break;
                        }
                    }
                }
            }
            //skip comments number and read comments
            getline(postinfo,line);//skip comments number
            if(user[j].posts[i-1].num_comments > 0){//read comments
                for(unsigned int k = 0; k < user[j].posts[i-1].num_comments; k++){
                    getline(postinfo,line);//read username
                    for(int m = 1; m <= n; m++){
                        if(user[m].username == line){
                            user[j].posts[i-1].comments[k].user = &user[m];
                            break;
                        }
                    }
                    getline(postinfo,line);//read comments text
                    user[j].posts[i-1].comments[k].text = line;
                }
            }
            //assign owner
            user[j].posts[i-1].owner = &user[j];
            //close the file
            postinfo.close();
            }
        }
    }
    
    //logfile!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    ifstream log;
    log.open(logname);
    string line;
    while(getline(log,line)){
        int order = 0;
        //trending
        int position_trending = line.find("trending");
        int position_visit = line.find("visit");
        int position_refresh = line.find("refresh");
        int position_follow = line.find("follow");
        int position_post = line.find("post");
        int position_like = line.find("like");
        int position_comment = line.find("comment");
        int position_unlike = line.find("unlike");
        int position_uncomment = line.find("uncomment");
        int position_delete = line.find("delete");
        int position_unfollow = line.find("unfollow");
        if(position_trending >= 0/*TODO:WRONG!*/){
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
    //clear all tag score to 0
    for(int i = 0; i < current_tag_struct_num; i++){
        tag[i].tag_score = 0;
    }
        }
        else if(position_visit > 0){// not yet test with g++
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
            User_t& r_user = user[user2_order];
            //printUser(r_user,relationship);
            cout << user[user2_order].username << endl;
            cout << relationship << endl;
            cout << "Followers: " << user[user2_order].num_followers
            << "\nFollowing: " << user[user2_order].num_following << endl;
        }
        else if(position_follow > 0 && position_unfollow < 0){
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
        else if(position_refresh > 0){
            cout << ">> refresh" << endl;
            string user1name;
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
        else if(position_post > 0){
            cout << ">> post" << endl;
            string user1name;
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
            user[user1_order].posts[user[user1_order].num_posts].title = line;
            //get tags
            int t = 0;
            while(1){
                getline(log,line);
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
        }
        else if(position_like > 0 && position_unlike < 0){
            cout << ">> like" << endl;
            string user1name;
            string user2name;
            string post_number;
            //get the name of two users
            for(int i = 0; i < position_like - 1; i++){
                user1name = user1name + line[i];
            }
            int j = position_like + 5;
            while(line[j] != ' '){
                user2name = user2name + line[j];
                j++;
            }
            //skip the space
            j++;
            //get the post number
            unsigned int like_post_num;
            while(line[j]){
                post_number = post_number + line[j];
                j++;
            }
            like_post_num = atoi(post_number.c_str());
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
            //check exception
                //1. no user2 post
	        try{
	        if(user[user2_order].num_posts < like_post_num){
	            ostringstream oStream;
	            oStream << "Error: " << user[user1_order].username << " cannot like post #"
                << like_post_num << " of " << user[user2_order].username << "!" << endl;
	            oStream << user[user2_order].username 
                <<  "does not have post #" << like_post_num << "." << endl;
	            throw Exception_t(INVALID_LOG, oStream.str());
	            }
            }
            catch (Exception_t &exception){
                cout << exception.error_info;
	            continue;
            }
                //2. user1 alreaday like this post
            int flag = 0;// judge whether user1 alreaday like this post
            for(unsigned int i = 0; i < user[user2_order].posts[like_post_num-1].num_likes; i++){
                if(user[user2_order].posts[like_post_num-1].like_users[i]->username == user1name){
                    flag = 1;
                    break;
                }
            }
	        try{
	        if(flag == 1){
	            ostringstream oStream;
	            oStream << "Error: " << user[user1_order].username << " cannot like post #"
                << like_post_num << " of " << user[user2_order].username << "!" << endl;
	            oStream << user[user1_order].username 
                <<  " has already like post #" << like_post_num 
                << " of " << user[user2_order].username << "." << endl;
	            throw Exception_t(INVALID_LOG, oStream.str());
	            }
            }
            catch (Exception_t &exception){
                cout << exception.error_info;
	            continue;
            }
            //if no exception
            user[user2_order].posts[like_post_num-1].like_users[user[user2_order].posts[like_post_num-1].num_likes] = &user[user1_order];
            user[user2_order].posts[like_post_num-1].num_likes++;
        }
        else if(position_comment > 0 && position_uncomment < 0){
            cout << ">> comment" << endl;
            string user1name;
            string user2name;
            string post_number;
            //get the name of two users
            for(int i = 0; i < position_comment - 1; i++){
                user1name = user1name + line[i];
            }
            int j = position_comment + 8;
            while(line[j] != ' '){
                user2name = user2name + line[j];
                j++;
            }
            //skip the space
            j++;
            //get the post number
            unsigned int comment_post_num;
            while(line[j]){
                post_number = post_number + line[j];
                j++;
            }
            comment_post_num = atoi(post_number.c_str());
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
            //check exception
            //no post of user2
	        try{
	        if(user[user2_order].num_posts < comment_post_num){
	            ostringstream oStream;
	            oStream << "Error: " << user[user1_order].username << " cannot comment post #"
                << comment_post_num << " of " << user[user2_order].username << "!" << endl;
	            oStream << user[user2_order].username 
                <<  " does not have post #" << comment_post_num << "." << endl;
	            throw Exception_t(INVALID_LOG, oStream.str());
	            }
            }
            catch (Exception_t &exception){
                cout << exception.error_info;
	            continue;
            }
            //read the comment
            getline(log,line);
            user[user2_order].posts[comment_post_num-1].comments[user[user2_order].posts[comment_post_num-1].num_comments].text = line;
            user[user2_order].posts[comment_post_num-1].comments[user[user2_order].posts[comment_post_num-1].num_comments].user = &user[user1_order];
            user[user2_order].posts[comment_post_num-1].num_comments++;
        }
        else if(position_unlike > 0){
            cout << ">> unlike" << endl;
            string user1name;
            string user2name;
            string post_number;
            //get the name of two users
            for(int i = 0; i < position_unlike - 1; i++){
                user1name = user1name + line[i];
            }
            int j = position_unlike + 7;
            while(line[j] != ' '){
                user2name = user2name + line[j];
                j++;
            }
            //skip the space
            j++;
            //get the post number
            unsigned int unlike_post_num;
            while(line[j]){
                post_number = post_number + line[j];
                j++;
            }
            unlike_post_num = atoi(post_number.c_str());
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
            //check exception
                //1. no user2 post
	        try{
	        if(user[user2_order].num_posts < unlike_post_num){
	            ostringstream oStream;
	            oStream << "Error: " << user[user1_order].username << " cannot unlike post #"
                << unlike_post_num << " of " << user[user2_order].username << "!" << endl;
	            oStream << user[user2_order].username 
                <<  " does not have post #" << unlike_post_num << "." << endl;
	            throw Exception_t(INVALID_LOG, oStream.str());
	            }
            }
            catch (Exception_t &exception){
                cout << exception.error_info;
	            continue;
            }
                //2. user1 alreaday unlike this post
            int flag = 1;// judge whether user1 alreaday unlike this post
            int like_user_order;
            for(unsigned int i = 0; i < user[user2_order].posts[unlike_post_num-1].num_likes; i++){
                if(user[user2_order].posts[unlike_post_num-1].like_users[i]->username == user[user1_order].username){
                    flag = 0;
                    like_user_order = i;
                    break;
                }
            }
	        try{
	        if(flag == 1){
	            ostringstream oStream;
	            oStream << "Error: " << user[user1_order].username << " cannot unlike post #"
                << unlike_post_num << " of " << user[user2_order].username << "!" << endl;
	            oStream << user[user1_order].username 
                <<  " has not liked post #" << unlike_post_num 
                << " of " << user[user2_order].username << "." << endl;
	            throw Exception_t(INVALID_LOG, oStream.str());
	            }
            }
            catch (Exception_t &exception){
                cout << exception.error_info;
	            continue;
            }
            //if no exception
            //release the pointer!!! and -1 the num_likes;
            user[user2_order].posts[unlike_post_num-1].like_users[like_user_order] = NULL;
            user[user2_order].posts[unlike_post_num-1].num_likes--;

        }
        else if(position_uncomment > 0){
            cout << ">> uncomment" << endl;
            string user1name;
            string user2name;
            string post_number;
            string comment_number;
            //get the name of two users
            for(int i = 0; i < position_uncomment - 1; i++){
                user1name = user1name + line[i];
            }
            int j = position_uncomment + 10;
            while(line[j] != ' '){
                user2name = user2name + line[j];
                j++;
            }
            //skip the space
            j++;
            //get the post number
            unsigned int uncomment_post_num;
            while(line[j] != ' '){
                post_number = post_number + line[j];
                j++;
            } 
            uncomment_post_num = atoi(post_number.c_str());

            //skip the space
            j++;
            //get the comment number
            unsigned int uncomment_comment_num;
            while(line[j]){
                comment_number = comment_number + line[j];
                j++;
            }
            uncomment_comment_num = atoi(comment_number.c_str());

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

            //check exception
                //1.no user2 post
	        try{
	        if(user[user2_order].num_posts < uncomment_post_num){
	            ostringstream oStream;
	            oStream << "Error: " << user[user1_order].username << " cannot uncomment comment #"
                << uncomment_comment_num << " of post #" << uncomment_post_num
                << " posted by " << user[user2_order].username << "!" << endl;
	            oStream << user[user2_order].username 
                <<  " does not have post #" << uncomment_post_num << "." << endl;
	            throw Exception_t(INVALID_LOG, oStream.str());
	            }
            }
            catch (Exception_t &exception){
                cout << exception.error_info;
	            continue;
            }
                //2.whether the post of user2 has the comment
	        try{
	        if(user[user2_order].posts[uncomment_post_num-1].num_comments < uncomment_comment_num){
	            ostringstream oStream;
	            oStream << "Error: " << user[user1_order].username << " cannot uncomment comment #"
                << uncomment_comment_num << " of post #" << uncomment_post_num
                << " posted by " << user[user2_order].username << "!" << endl;
	            oStream << user[user2_order].username 
                <<  " does not have comment #" << uncomment_comment_num << "." << endl;
	            throw Exception_t(INVALID_LOG, oStream.str());
	            }
            }
            catch (Exception_t &exception){
                cout << exception.error_info;
	            continue;
            }
                //3.whether user1 is the owner of the comment
	        try{
	        if(user[user2_order].posts[uncomment_post_num-1].comments[uncomment_comment_num-1].user->username != user[user1_order].username){
	            ostringstream oStream;
	            oStream << "Error: " << user[user1_order].username << " cannot uncomment comment #"
                << uncomment_comment_num << " of post #" << uncomment_post_num
                << " posted by " << user[user2_order].username << "!" << endl;
	            oStream << user[user2_order].username 
                <<  " is not the owner of comment #" << uncomment_comment_num << "." << endl;
	            throw Exception_t(INVALID_LOG, oStream.str());
	            }
            }
            catch (Exception_t &exception){
                cout << exception.error_info;
	            continue;
            }

            //if no exception, then remove the comment and number of comments -1
            user[user2_order].posts[uncomment_post_num-1].comments[uncomment_comment_num-1].user = NULL;
            user[user2_order].posts[uncomment_post_num-1].comments[uncomment_comment_num-1].text = "";
            user[user2_order].posts[uncomment_post_num-1].num_comments--;
        }
        else if(position_delete > 0){
            cout << ">> delete" << endl;
            string user1name;
            string post_number;
            //get the name of two users
            for(int i = 0; i < position_delete - 1; i++){
                user1name = user1name + line[i];
            }
            int j = position_delete + 7;
            //get the post number
            unsigned int post_num;
            while(line[j]){
                post_number = post_number + line[j];
                j++;
            }
            post_num = atoi(post_number.c_str());
            // get orders of user1
            int user1_order = 1;
            while(1){
                if(user[user1_order].username == user1name) break;
                else user1_order++;
            }
            //check exception
                //1.no user2 post
	        try{
	        if(user[user1_order].num_posts < post_num){
	            ostringstream oStream;
	            oStream << "Error: " << user[user1_order].username << " cannot delete post #"
                << post_num << "!" << endl;
	            oStream << user[user1_order].username 
                <<  " does not have post #" << post_num << "." << endl;
	            throw Exception_t(INVALID_LOG, oStream.str());
	            }
            }
            catch (Exception_t &exception){
                cout << exception.error_info;
	            continue;
            }
            
            //if no exception
            //delete comments
            for(unsigned int i = 0; i < user[user1_order].posts[post_num-1].num_comments; i++){
                user[user1_order].posts[post_num-1].comments[i].text = "";
                user[user1_order].posts[post_num-1].comments[i].user = NULL;
            }
            //delete like users
            for(unsigned int i = 0; i < user[user1_order].posts[post_num-1].num_likes; i++){
                user[user1_order].posts[post_num-1].like_users[i] = NULL;
            }
            //delete tags
            for(unsigned int i = 0; i < user[user1_order].posts[post_num-1].num_tags; i++){
                user[user1_order].posts[post_num-1].tags[i] = "";
            }
            //delete owners
            user[user1_order].posts[post_num-1].owner = NULL;
            //delete title
            user[user1_order].posts[post_num-1].title = "";
            //delete text
            user[user1_order].posts[post_num-1].text = "";
            //clear all numbers back to zero
            user[user1_order].posts[post_num-1].num_comments = 0;
            user[user1_order].posts[post_num-1].num_likes = 0;
            user[user1_order].posts[post_num-1].num_tags = 0;

        }
        else if(position_unfollow > 0){
            cout << ">> unfollow" << endl;
            string user1name;
            string user2name;
            //get the name of two users
            for(int i = 0; i < position_unfollow - 1; i++){
                user1name = user1name + line[i];
            }
            int j = position_unfollow + 9;
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
            //unfollow! following and follower number--
            for(unsigned int i = 0; i < user[user1_order].num_following; i++){
                if(user[user1_order].following[i]->username == user[user2_order].username){
                    user[user1_order].following[i] = NULL;
                }
            }
            for(unsigned int i = 0; i < user[user2_order].num_followers; i++){
                if(user[user2_order].follower[i]->username == user[user1_order].username){
                    user[user2_order].follower[i] = NULL;
                }
            }
            user[user1_order].num_following--;
            user[user2_order].num_followers--;
        }
    }
    log.close();
    return 0;
}