#include "ex1.h"

int dot(list_t v1, list_t v2){
	// TODO: implement dot function
	if(list_isEmpty(v1) || list_isEmpty(v2)){
		return 0;
	}
	else{
		int l1 = 0; 
		int l2 = 0;
		list_t temp = v1;
		while(1){
			if(list_isEmpty(temp)) break;
			else{
				l1++;
				temp = list_rest(temp);
			}
		}
		temp = v2;
		while(1){
			if(list_isEmpty(temp)) break;
			else{
				l2++;
				temp = list_rest(temp);
			}
		}

		int length = 0;
		if(l1 < l2) length = l1;
		else length = l2;

		//calculate the dot product
		int ans = 0;
		for(int i = 0; i < length; i++){
			ans += list_first(v1)*list_first(v2);
			v1 = list_rest(v1);
			v2 = list_rest(v2);
		}
		return ans;

	}
}

list_t filter_odd(list_t list){
	// TODO: implement filter_odd function
	list_t odd_list = list_make();
	list_t temp = list;
	int l1 = 0;
	while(1){
		if(list_isEmpty(temp)) break;
		else{
			l1++;
			temp = list_rest(temp);
			}
	}

	int odd_number[l1] = {0};
	int num_odd = 0;
	while(1){
		if(list_isEmpty(list)) break;
		else{
			if(list_first(list) % 2 != 0){
				odd_number[num_odd] = list_first(list);
				num_odd++;
			}
			list = list_rest(list);
		}
	}
	for(int i = num_odd - 1; i >= 0; i--){
		odd_list = list_make(odd_number[i],odd_list);
	}
	return odd_list;
}

list_t filter(list_t list, bool (*fn)(int)){
	// TODO: implement filter function
	list_t ans_list = list_make();
	list_t temp = list;
	int l1 = 0;
	while(1){
		if(list_isEmpty(temp)) break;
		else{
			l1++;
			temp = list_rest(temp);
			}
	}

	int ans_number[l1] = {0};
	int num_ans = 0;
	while(1){
		if(list_isEmpty(list)) break;
		else{
			if(fn(list_first(list))){
				ans_number[num_ans] = list_first(list);
				num_ans++;
			}
			list = list_rest(list);
		}
	}
	for(int i = num_ans - 1; i >= 0; i--){
		ans_list = list_make(ans_number[i],ans_list);
	}
	return ans_list;
}

