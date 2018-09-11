
#include"hashmap.h"

node * create_node()
{
	node * newnode;
	newnode = malloc(sizeof(node));
	newnode->next = NULL;
	return newnode;
}
HashMap * create_hashmap(size_t key_space)
{
	if(key_space == 0)
	{
		printf("keysapce cannot be zero\n");
	}
	HashMap * hm = NULL;
	hm = calloc(key_space, sizeof(HashMap));
	hm->key_space = key_space;
	return hm;
}
uint32_t hash(const char *key)
{
	uint32_t sum=0;
	while (*key)
	{
		sum = sum + (int)*key;
    	key++;
	}
	return sum;
}
void insert_data (HashMap *hm, const char *key, void *data, void *(*resolve_collision)(void *, void *))
{
	int flag = 0;
	void *new_data = data;
	HashMap *temp = hm;
	uint32_t index = (hash(key) % hm->key_space);
	temp = temp + index;

	if (temp->head == NULL)
	{
		node * newnode = create_node();
		printf("\n****New key*****\n");
		newnode->next = NULL;
		newnode->val = data;
		newnode->key = key;
		temp->head = newnode;
	}

	else
	{
		node * t_node = temp->head;
		while(t_node != NULL )
		{
			if(t_node->key == key)
			{
				new_data = resolve_collision(t_node->val, data);
				t_node->val = new_data;
				flag = 1;
				break;
			}
			else
			{
				t_node = t_node->next;
			}
		}
		if(flag != 1)
		{
			t_node = create_node();

			t_node->next = temp->head;
			t_node->key = key;
			t_node->val = new_data;
			temp->head = t_node;
		}
	}
}
void *get_data (HashMap *hm, const char *key)
{

	if(key == NULL)
	{
		return NULL;
	}
	HashMap * temp = hm;
	uint32_t index = (hash(key) % hm->key_space);
	temp = temp + index;
	if (temp->head == NULL){
	//	printf("no key present\n");
		return NULL;
	}
	else{
		node * t_node = temp->head;
		while (t_node != NULL)
		{
			if (t_node->key == key)
			{
				return t_node->val;
			}
			else t_node = t_node->next;
		}
		return NULL;
	}
}
void remove_data(HashMap *hm, const char *key, void(*destroy_data)(void *))
{
	HashMap *temp = hm;
	uint32_t index = (hash(key) % hm->key_space);
	temp = temp + index;
	node * current = temp->head;
	node * t_node ;

		if(current == NULL)
		{
			return;
		}

		t_node = current;
		while(current != NULL)
		{
			if(current->key == key)
			{
				if (destroy_data != NULL)
				{
					destroy_data(current->val);
				}
				if(current == temp->head)
				{
					temp->head = current->next;
				}
				else
				{
					t_node->next = current->next;
				}
				free(current);
				break;
			}
			t_node = current;
			current = current->next;
		}
}
void iterate(HashMap *hm, void callback(void *,void *))
{
	int index = 0;
	HashMap *temp = hm;

	while (index < hm->key_space)
	{
		if (temp->head == NULL)
		{
			index++;
			temp++;
		}
		else
		{
			node * t_node = temp->head;
			while (t_node != NULL)
			{
				callback(t_node->key, t_node->val);
				t_node = t_node->next;
			}

			index++;
			temp++;
		}
	}
}
void delete_hashmap(HashMap *hm, void(*destroy_data)(void *))
{
	HashMap * temp = hm;
	int index = 0;

	while (index < hm->key_space)
	{
		if(temp->head == NULL)
		{
			index++;
			temp++;
		}
		else
		{
			node * current = temp->head;
			while(temp->head != NULL)
			{
					if(destroy_data != NULL)
				{
					destroy_data(current->val);
				}
				if(current->next == NULL)
				{
					free(current);
					index++;
					temp++;
					break;
				}
				temp->head = current->next;
				free(current);
				current = temp->head;
			}
		}
	}
	free(hm);
 }

