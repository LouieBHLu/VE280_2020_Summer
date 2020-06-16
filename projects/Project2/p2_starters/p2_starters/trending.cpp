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
            printTag(tag[i],i+1);
            //cout << i+1 << " " << tag[i].tag_content << ": " << tag[i].tag_score << endl;
        }
    }
    else{
        for(int i = 0; i < top_n; i++){
            // const Tag_t &r_tag = tag[i];
            // printTag(r_tag, i+1);
            printTag(tag[i],i+1);
            //cout << i+1 << " " << tag[i].tag_content << ": " << tag[i].tag_score << endl;
        }
    }
    //clear all tag score to 0
    for(int i = 0; i < current_tag_struct_num; i++){
        tag[i].tag_score = 0;
        tag[i].tag_content = "";
    }
