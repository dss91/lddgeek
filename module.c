#include<linux/module.h>
#include<linux/init.h>

static int __init  _start_up(void){
	printk("Hellow World!\n");
return 0;
}
static void __exit _clean_up(void){
	printk("Bye Bhai\n");

}

module_init(_start_up);
module_exit(_clean_up);
