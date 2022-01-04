#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/printk.h>
#include<linux/uaccess.h>



#define WRITE_ARRAY _IOW('a','a',int32_t*)
#define READ_ARRAY _IOR('a','b',int32_t*)


struct my_data {
    int arr;
    int dd;
};


int	mod_open (struct inode *inode, struct file *filep)
{
    pr_info("module open .. \n");
    return 0;
}

struct my_data value[5];

long mod_ioctl(struct file *filep, unsigned int flag, unsigned long arg)
{
    pr_info("ioctl operations called ..\n");
    switch(flag)
    {
        case WRITE_ARRAY:
                        pr_info("write array  called ..\n");
                        if(copy_from_user(value ,(struct my_data*) arg, (sizeof(struct my_data) *5)) )
                        {
                            pr_err("Data Write : Err!\n");
                        }
                        pr_info("Value = %d\n", value[3].arr);
                        pr_info("Value = %d\n", value[3].dd);
                        
                        break;
        case READ_ARRAY:
                        pr_info("read array called..\n");
                        if(copy_to_user((struct my_data *) arg , value , (sizeof(struct my_data) *5)))
                        {
                            pr_err("Data Read : Err..\n");
                        }  
                        break;
    
        default:
                        pr_info("No value specified");
                        break;


    }
    return 0;
}




static struct proc_ops myProcops = {
    .proc_open = mod_open,
    .proc_ioctl = mod_ioctl,

};




static int __init proModinit(void)
{
    pr_info("module initilization...\n");
    proc_create("ov426", 0, NULL, &myProcops);
    return 0;
}


static void __exit proModexit(void)
{
    pr_info("module exit..\n");
    remove_proc_entry("ov426", NULL);
}


module_init(proModinit);
module_exit(proModexit);

MODULE_AUTHOR("abhi");
MODULE_DESCRIPTION("proc module");
MODULE_LICENSE("GPL");
