/*
 * This is VE280 Project 2, SU2020.
 * Written by Ziqiao Ma and Zhuoer Zhu.
 * Latest Update: 5/29/2020.
 * All rights reserved.
 */

#include "server_type.h"

// TODO: Declare your functions in this header file.
void trending(string line, User_t user[], Tag_t tag[], int order, int n);
void visit(int position_visit, string line, User_t user[]);
void follow(int position_follow, string line, User_t user[]);
void refresh(int position_refresh, string line, User_t user[]);
void post(int position_post, string line, User_t user[], int *line_num, string logname);
void like(User_t user[],int user2_order, int user1_order, int like_post_num);
void comment(string line, User_t user[],int *line_num, string logname, int user2_order, int user1_order, int comment_post_num);

/*
void refresh(...);
void follow(...);
void unfollow(...);
void like(...);
void unlike(...);
void comment(...);
void uncomment(...);
void post(...);
void unpost(...);
*/

/* Helper Functions */

// Printing
void printUser(User_t& user, const string& relationship);
void printPost(Post_t& post);
void printTag(const Tag_t& tag, unsigned int rank);

