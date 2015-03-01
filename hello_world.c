/*
 *Hello World Program on Linux Kernel Modules on Beagle Bone Black
*/

#include<linux/module.h>		//Responsible for dynamic loading of modules in to kernel
#include<linux/init.h>			//declarations of module_init,__init,__exit etc are present
#include<linux/moduleparam.h>		//declarations of module parameter passing APIs
#include<linux/kernel.h>		//for kernel related APIs
#include<linux/stat.h>			//the permissions !

//Module Information which can be probed via "modinfo"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("dss91");
MODULE_DESCRIPTION("A Hello World Module");
MODULE_VERSION("0.1");

static 		char	*myname	  = "Shyam";
static long	int	my_mobile = 12345;
static 		char	*myaddress= "RKPuram,Delhi";
/*
 * Module paramerter can be of any type 
 * module_param(parameter, para_data_type, permissions)
 * 
 * permissions: S_IRWXU ignore S_I, Read(R) Write(W) eXecute(X) permissions for User(U)
 *              this flag is a conjunction of S_IRUSR | S_IWUSR | S_IXUSR
 *		similarly we can also have S_IRWXGRP,S_IRWXOTH
*/

module_param(myname, charp, S_IRWXU);
MODULE_PARM_DESC(myname,"Your Name");		// this would help if you probe module info using modinfo
module_param(my_mobile, long,S_IRWXU);
MODULE_PARM_DESC(my_mobile,"Your Mobile Number");
module_param(myaddress, charp, S_IRWXU);
MODULE_PARM_DESC(myaddress,"Your Address");

/*
 * as you know "static" before the function makes the function scope limited to file
 * __init is actually a macro which acts as a hint to  kernel that this is a kind of routine which is being used during 
 * initialization so after some time after the initialization is over this can be flushed from the memory
 * Reference /linux/init.h
 * Note: any way the LKM has no connection with these , these are only applied for built in drivers :) 
*/

static int __init  _start_up(void){
	printk("Hellow World!\n");
	printk("My Name is %s\n",myname);
	printk("My Mobile Number is %ld\n",my_mobile);
	printk("My Address is %s\n",myaddress);

return 0;
}

/*
 * __exit is similar hint to kernel as __init but quite opposite, and has no sense if used in LKMs its included only as its seen in every 
 * driver code, for a buit-in driver it says this can be discarded by kernel, 
 * (that is why after the module is inserted this function of _clean_up would be available for LKMs)  
 * Reference /linux/init.h
 * Note: any way the LKM has no connection with these , these are only applied for built in drivers :) 
*/

static void __exit _clean_up(void){
	printk("Bye World\n");

}

module_init(_start_up);
module_exit(_clean_up);
