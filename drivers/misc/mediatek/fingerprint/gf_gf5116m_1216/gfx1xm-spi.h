#ifndef __GFX1XM_SPI_H
#define __GFX1XM_SPI_H

#include <linux/types.h>
#include <linux/of_irq.h>
#include <linux/notifier.h>
#include <linux/spi/spi.h>
#include <mt_gpio.h>
#include <linux/platform_device.h>
#include <linux/of.h>//20160307
#include <mt_spi.h>//20160307
#include <mt_spi_hal.h>//20160307
//#include <kd_flashlight.h>
//#include <mach/mt_spi.h>
//#include <mach/eint.h>
//#include <cust_eint.h>
//#include "spi_dts_gpio.h"
#if defined(CONFIG_HAS_EARLYSUSPEND) && defined(USE_EARLY_SUSPEND)
#include <linux/earlysuspend.h>
#endif
#include <linux/hct_include/hct_project_all_config.h>
extern int hct_finger_set_reset(int cmd);
/****************GFX1XM Macro interface*******************/
#define FW_UPDATE                0//0
#define ESD_PROTECT              0
#ifndef __HCT_FP_GFX1XM_DRIVER_CFG_UPDATE__
#define __HCT_FP_GFX1XM_DRIVER_CFG_UPDATE__   0
#endif
#if __HCT_FP_GFX1XM_DRIVER_CFG_UPDATE__
#define CFG_UPDATE               1//0
#else
#define CFG_UPDATE               0//0
#endif

#define GFX1XM_DEBUG             1
#define CONFIG_HAS_EARLYSUSPEND  1
#define GFX1XM_FASYNC            1//If support fasync mechanism.
#ifdef CONFIG_ARM64
#define PROCESSOR_64_BIT         1//open 64 bit config  
#else
#define PROCESSOR_64_BIT         0
#endif
#define GFX18M_PID 							"GFx18M"       //IF you use GFx18M
//#define GFX16M_PID 						"GFx16M"			//IF you use GFX16M
#define FACTORY_MODE_TEST		0


#define GFX1XM_DRIVER_VERSION    "V1.2.1<20160101>"
#define GFX1XM_CONFIG_PROC_FILE  "gfx1xm_config"

#define MTK_SPI_ALIGN_MASK_NUM  10
#define MTK_SPI_ALIGN_MASK  ((0x1 << MTK_SPI_ALIGN_MASK_NUM) - 1)

#define GFX1XM_PID_LEN 6
/*
 * This supports access to SPI devices using normal userspace I/O calls.
 * Note that while traditional UNIX/POSIX I/O semantics are half duplex,
 * and often mask message boundaries, full SPI support requires full duplex
 * transfers.  There are several kinds of internal message boundaries to
 * handle chipselect management and other protocol options.
 *
 * SPI has a character major number assigned.  We allocate minor numbers
 * dynamically using a bitmask.  You must use hotplug tools, such as udev
 * (or mdev with busybox) to create and destroy the /dev/spidevB.C device
 * nodes, since there is no fixed association of minor numbers with any
 * particular SPI bus or device.
 */

/*spi device name*/
#define SPI_DEV_NAME        "spidev"
/*device name after register in charater*/
#define DEV_NAME            "goodix_fp"
#define	CHRD_DRIVER_NAME    "goodix"
#define	CLASS_NAME          "goodix-spi"
#define SPIDEV_MAJOR        156	/* assigned */
#define N_SPI_MINORS        32	/* ... up to 256 */

#define GFX1XM_INPUT_MENU_KEY   KEY_MENU
#define GFX1XM_INPUT_BACK_KEY   KEY_BACK
#define GFX1XM_INPUT_HOME_KEY   KEY_F11//KEY_HOMEPAGE
#define GFX1XM_FF_KEY           KEY_F10

/********************GFX1XM Mapping**********************/
#define GFX1XM_BASE             (0x8000)
#define GFX1XM_OFFSET(x)        (GFX1XM_BASE + x)

#define GFX1XM_VERSION	        GFX1XM_OFFSET(0)
#define GFX1XM_CONFIG_DATA      GFX1XM_OFFSET(0x40)
#define GFX1XM_CFG_ADDR	        GFX1XM_OFFSET(0x47)
#define GFX1XM_MODE_STATUS      GFX1XM_OFFSET(0x043)
//#define GFX1XM_MIXER_DATA     GFX1XM_OFFSET(0x140)
#define GFX1XM_BUFFER_STATUS    GFX1XM_OFFSET(0x140)
#define GFX1XM_KEY_DATA         GFX1XM_OFFSET(0x142)
#define GFX1XM_NOISE_DATA       GFX1XM_OFFSET(0x144)
#define GFX1XM_LONG_PRESS_STDP  GFX1XM_OFFSET(0x146)
#define GFX1XM_BUFFER_DATA      GFX1XM_OFFSET(0x141)


#define GFX1XM_BUF_STA_MASK      (0x1<<7)
#define	GFX1XM_BUF_STA_READY     (0x1<<7)
#define	GFX1XM_BUF_STA_BUSY      (0x0<<7)

#define	GFX1XM_IMAGE_MASK        (0x1<<6)
#define	GFX1XM_IMAGE_ENABLE      (0x1)
#define	GFX1XM_IMAGE_DISABLE     (0x0)

#define	GFX1XM_KEY_MASK	         (GFX1XM_HOME_KEY_MASK | \
                                  GFX1XM_MENU_KEY_MASK | \
                                  GFX1XM_BACK_KEY_MASK )

//home key
#define	GFX1XM_HOME_KEY_MASK    (0x1<<5)
#define	GFX1XM_HOME_KEY_ENABL   (0x1)
#define	GFX1XM_HOME_KEY_DISABLE (0x0)
#define	GFX1XM_HOME_KEY_STA     (0x1<<4)
//menu key
#define	GFX1XM_MENU_KEY_MASK    (0x1<<3)
#define	GFX1XM_MENU_KEY_ENABLE	(0x1)
#define	GFX1XM_MENU_KEY_DISABLE	(0x0)
#define	GFX1XM_MENU_KEY_STA     (0x1<<2)
//back key
#define	GFX1XM_BACK_KEY_MASK    (0x1<<1)
#define	GFX1XM_BACK_KEY_ENABLE  (0x1)
#define	GFX1XM_BACK_KEY_DISABLE (0x0)
#define	GFX1XM_BACK_KEY_STA     (0x1<<0)
#define	GFX1XM_IMAGE_MODE       (0x00)
#define	GFX1XM_KEY_MODE	        (0x01)
#define GFX1XM_SLEEP_MODE       (0x02)
#define GFX1XM_FF_MODE          (0x03)
#define GFX1XM_DEBUG_MODE       (0x56)

/**********************GFX1XM ops****************************/
#define GFX1XM_W                0xF0
#define GFX1XM_R                0xF1
#define GFX1XM_WDATA_OFFSET     (0x3)
#define GFX1XM_RDATA_OFFSET     (0x5)
#define GFX1XM_CFG_LEN          (249)   /*config data length*/

/**********************************************************/

/**************************debug******************************/
#define DEFAULT_DEBUG   (0)
#define SUSPEND_DEBUG   (1)
#define SPI_DEBUG       (2)
#define TIME_DEBUG      (3)
#define FLOW_DEBUG      (4)
static int g_debug_level = FLOW_DEBUG;//DEFAULT_DEBUG;

#if GFX1XM_DEBUG
		#define gfx1xm_debug(level, fmt, args...) do{ \
		    if(g_debug_level >= level) {\
			printk("gfx1xm"fmt"\n", ##args); \
		    } \
		}while(0)
#else
		#define gfx1xm_debug(level, fmt, args...) do{ \
		    if(0) {\
			printk("gfx1xm"fmt"\n", ##args); \
		    } \
		}while(0)
#endif
#define gfx1xm_error(fmt,arg...)          printk("gfx1xm_error %s"fmt"\n",__func__,##arg)  

#define FUNC_ENTRY()  gfx1xm_debug(FLOW_DEBUG, "gfx1xm:%s, entry\n", __func__)
#define FUNC_EXIT()  gfx1xm_debug(FLOW_DEBUG,"gfx1xm:%s, exit\n", __func__)




/*************************************************************/
struct gfx1xm_dev {
#if CFG_UPDATE	
	u8 config[GFX1XM_CFG_LEN+GFX1XM_WDATA_OFFSET];
#endif
	dev_t devt;
	spinlock_t spi_lock;
	struct spi_device *spi;
	struct list_head device_entry;
	struct input_dev *input;
#if ESD_PROTECT
	int clk_tick_cnt;
	struct delayed_work esd_check_work;
	struct workqueue_struct *esd_wq;
#endif
	/* buffer is NULL unless this device is open (users > 0) */
	struct mutex buf_lock;
	struct mutex fb_lock;
	unsigned long irq_gpio;
	unsigned long reset_gpio;
	unsigned long power_gpio;
	unsigned int poweron;
	unsigned int esd_running;
	unsigned users;
	u8 *buffer;	
	u8 buf_status;
	u8 mode;
    struct pinctrl *pctrl;	
     //  unsigned int fp_irq;
     //  struct regulator *reg;
     //  struct pinctrl *pinctrl1;
     //  struct pinctrl_state *pins_default;
     //  struct pinctrl_state *eint_as_int, *eint_in_low, *eint_in_float, *fp_rst_low, *fp_rst_high,*miso_pull_up,*miso_pull_disable;
#ifdef GFX1XM_FASYNC
	struct fasync_struct *async;
#endif
#if defined(CONFIG_HAS_EARLYSUSPEND) && defined(USE_EARLY_SUSPEND)
    struct early_suspend early_fp;
#endif
	struct work_struct	eint_work;

	/* flag used for goodix device */
	u8 old_mode;
	unsigned int irq_flag;
	unsigned int early_suspend_flag;
	unsigned int chip_version_config;
	unsigned int irq_enabled_flag;
	struct class *gfx1xm_spi_class;
	struct task_struct *gfx1xm_irq_thread;

};


#if CFG_UPDATE
static const u8 vendor_id_1[3]={0xFF};
static const u8 vendor_id_2[3]={0x00};

/**************************config for GFx18M use********************************************/
//default is for GF318M  AES OFF
#if __HCT_FP_GFX1XM_DRIVER_CFG_UPDATE__
#define GFX18M_CFG_GROUP0 __HCT_GFX18M_CFG_GROUP0__
#else
#define GFX18M_CFG_GROUP0 {\
}
#endif
//default is for GF318M  AES OFF
#if __HCT_FP_GFX1XM_DRIVER_CFG_UPDATE__
#define GFX18M_CFG_GROUP1 __HCT_GFX18M_CFG_GROUP0__
#else
#define GFX18M_CFG_GROUP1 {\
}
#endif
/*****************************config for GFx16M use*******************************************/
//default is for GF316M  //AES OFF
#define GFX16M_CFG_GROUP0 {\
0x41,0x3c,0x3c,0xe4,0x0c,0x30,0x3f,0x02,0x00,0x50,0x40,0x50,0x50,0xe4,0x0c,0x30,\
0x2f,0x03,0x40,0x03,0x11,0xa0,0x0d,0x00,0x14,0x03,0x0f,0x0f,0x0f,0xb2,0x3f,0xb3,\
0x33,0x03,0x90,0x01,0x40,0x05,0x0e,0x80,0x20,0x0f,0x22,0x00,0x08,0x10,0x12,0x11,\
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,\
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,\
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,\
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,\
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,0xe8,0x25,0x04,0xca,0xa4,0x26,0x66,0x00,\
0x00,0x00,0x01,0x00,0x01,0x0f,0x96,0x00,0x01,0x02,0x85,0x00,0x03,0x20,0x20,0x50,\
0x3e,0x11,0x01,0x00,0x00,0x00,0x00,0x03,0x09,0x00,0x31,0x00,0x07,0x14,0x41,0x00,\
0x50,0x00,0x00,0x00,0x20,0x00,0x04,0x00,0x32,0x01,0xa0,0x00,0x00,0x79,0xc8,0x00,\
0x00,0x00,0x28,0x00,0x05,0x04,0x30,0x00,0x08,0x00,0x07,0x00,0x20,0x00,0x18,0x00,\
0x3b,0x00,0x5d,0x00,0x22,0x00,0x00,0x00,0x03,0x07,0x80,0x00,0x20,0x00,0x20,0x00,\
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,\
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,\
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xD3,0x01,\
}
//default is for GF316M  //AES OFF
#define GFX16M_CFG_GROUP1 {\
0x41,0x3c,0x3c,0xe4,0x0c,0x30,0x3f,0x02,0x00,0x50,0x40,0x50,0x50,0xe4,0x0c,0x30,\
0x2f,0x03,0x40,0x03,0x11,0xa0,0x0d,0x00,0x14,0x03,0x0f,0x0f,0x0f,0xb2,0x3f,0xb3,\
0x33,0x03,0x90,0x01,0x40,0x05,0x0e,0x80,0x20,0x0f,0x22,0x00,0x08,0x10,0x12,0x11,\
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,\
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,\
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,\
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,\
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,0xe8,0x25,0x04,0xca,0xa4,0x26,0x66,0x00,\
0x00,0x00,0x01,0x00,0x01,0x0f,0x96,0x00,0x01,0x02,0x85,0x00,0x03,0x20,0x20,0x50,\
0x3e,0x11,0x01,0x00,0x00,0x00,0x00,0x03,0x09,0x00,0x31,0x00,0x07,0x14,0x41,0x00,\
0x50,0x00,0x00,0x00,0x20,0x00,0x04,0x00,0x32,0x01,0xa0,0x00,0x00,0x79,0xc8,0x00,\
0x00,0x00,0x28,0x00,0x05,0x04,0x30,0x00,0x08,0x00,0x07,0x00,0x20,0x00,0x18,0x00,\
0x3b,0x00,0x5d,0x00,0x22,0x00,0x00,0x00,0x03,0x07,0x80,0x00,0x20,0x00,0x20,0x00,\
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,\
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,\
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xD3,0x01,\
}

#endif

/**********************IO Magic**********************/
#define  GFX1XM_IOC_MAGIC    'g'  //define magic number
struct gfx1xm_ioc_transfer {
	u8	cmd;
	u8 reserve;
	u16	addr;
	u32 len;
#if PROCESSOR_64_BIT
	//u32  buf;//32BIT_SO
	u64  buf;//64BIT_SO
#else
	u8 *buf;
#endif
};

//define commands

/*read/write GFX1XM registers*/
#define  GFX1XM_IOC_CMD       _IOWR(GFX1XM_IOC_MAGIC, 1, struct gfx1xm_ioc_transfer)
#define  GFX1XM_IOC_REINIT    _IO(GFX1XM_IOC_MAGIC, 0)
#define  GFX1XM_IOC_SETSPEED  _IOW(GFX1XM_IOC_MAGIC, 2, u32)
#define  GFX1XM_IOC_SLEEP    _IO(GFX1XM_IOC_MAGIC, 3)
//#define  GFX1XM_IOC_DISABLE    _IO(GFX1XM_IOC_MAGIC, 3)
//#define  GFX1XM_IOC_ENABLE     _IO(GFX1XM_IOC_MAGIC, 4)

#define  GFX1XM_IOC_MAXNR    3

/*******************Refering to hardware platform*****************************/
typedef enum tagDTS_GPIO_STATE {
	//DTS_GPIO_STATE_SPI_CS_OUT0 = 0,	/* mode_te_gpio */
	//DTS_GPIO_STATE_SPI_CS_OUT1,	/* mode_te_te */
	DTS_GPIO_STATE_SPI_MI_PULLUP,
	DTS_GPIO_STATE_SPI_MI_PULLDISABLE,
	/*DTS_GPIO_STATE_SPI_MO_OUT0,
	DTS_GPIO_STATE_SPI_MO_OUT1,
	DTS_GPIO_STATE_SPI_CLK_OUT0,
	DTS_GPIO_STATE_SPI_CLK_OUT1,*/
	DTS_GPIO_STATE_FINGER_RST0,
	DTS_GPIO_STATE_FINGER_RST1,
	DTS_GPIO_STATE_FINGER_POWER0,
	DTS_GPIO_STATE_FINGER_POWER1,
	/*DTS_GPIO_STATE_AS_EINT,
	DTS_GPIO_STATE_EINT_IN_LOW,	
	DTS_GPIO_STATE_EINT_IN_HIGH,*/
	DTS_GPIO_STATE_MAX,	/* for array size */
} SPI_DTS_GPIO_STATE;
static struct pinctrl *this_pctrl; /* static pinctrl instance */
/* DTS state mapping name */
static const char *this_state_name[DTS_GPIO_STATE_MAX] = {
	/*"spi_cs_low",
	"spi_cs_high",*/
	"miso_pull_up",
	"miso_pull_disable",
	/*"spi_mo_low",
	"spi_mo_high",
	"spi_mclk_low",
	"spi_mclk_high",*/
	"finger_rst_low",
	"finger_rst_high",
	"finger_power_low",
	"finger_power_high",
	/*"eint",
	"eint_in_low",
	"eint_in_float"*/
};

/* pinctrl implementation */
inline static long _set_state(const char *name)
{
	long ret = 0;
	struct pinctrl_state *pState = 0;

	BUG_ON(!this_pctrl);

	pState = pinctrl_lookup_state(this_pctrl, name);
	if (IS_ERR(pState)) {
		pr_err("finger set state '%s' failed\n", name);
		ret = PTR_ERR(pState);
		return ret;
	}
	/* select state! */
	pinctrl_select_state(this_pctrl, pState);
	return ret;
}

#if 0
inline static long spi_dts_gpio_init(struct  gfx1xm_dev *pdev)
{
	long ret = 0;
	//struct pinctrl *pctrl;
	struct pinctrl_state *pState = 0;
	int i;
	struct device_node *node;
	
	//pctrl = devm_pinctrl_get(&pdev->dev);
	node = of_find_compatible_node(NULL, NULL,"mediatek,goodix-fp");
	if(node) {
		gfx1xm_debug(DEFAULT_DEBUG,"%s:get node success\n",__func__);
		for(i=0;i<DTS_GPIO_STATE_MAX;i++) {
			pState = pinctrl_lookup_state(pdev->pctrl, this_state_name[i]);
			if (IS_ERR(pState)) {
				pr_err("spi_dts_gpio_init gpio_name=%s failed\n",  this_state_name[i]);
				ret = PTR_ERR(pState);
				return ret;
			}
		}
		gfx1xm_debug(DEFAULT_DEBUG,"%s:success\n",__func__);
		this_pctrl = pdev->pctrl;
	} else {
		pr_err("spi_dts_gpio_init get node failed\n");
	}
	return ret;
}
#endif
inline static long spi_dts_gpio_select_state(SPI_DTS_GPIO_STATE s)
{
	BUG_ON(!((unsigned int)(s) < (unsigned int)(DTS_GPIO_STATE_MAX)));
	return _set_state(this_state_name[s]);
}

/*Confure the IRQ pin for GFX1XM irq if necessary*/
inline static void gfx1xm_spi_pins_config(void)
{
	//fix me:TODO
}
inline static void gfx1xm_irq_cfg(struct gfx1xm_dev *gfx1xm_dev)
{
	//fix me:TODO
}

/********************************************************************
*CPU output low level in RST pin to reset GFX1XM. This is the MUST action for GFX1XM.
*Take care of this function. IO Pin driver strength / glitch and so on.
********************************************************************/
inline static void gfx1xm_hw_reset(struct gfx1xm_dev *gfx1xm_dev, int ms)
{	
	gfx1xm_debug(DEFAULT_DEBUG, "gfx1xm_hw_reset\n");

	//spi_dts_gpio_select_state(DTS_GPIO_STATE_SPI_MI_PULLUP);
	//msleep(5);	
	//spi_dts_gpio_select_state(DTS_GPIO_STATE_FINGER_RST0);
        hct_finger_set_reset(0);
	msleep(5); 
        hct_finger_set_reset(1);
//	spi_dts_gpio_select_state(DTS_GPIO_STATE_FINGER_RST1);
	if (ms)
	    msleep(ms);
	//spi_dts_gpio_select_state(DTS_GPIO_STATE_SPI_MI_PULLDISABLE);	

}

int gfx1xm_spi_read_bytes(struct gfx1xm_dev *gfx1xm_dev,
                                u16 addr, u32 data_len, u8 *rx_buf);

int gfx1xm_spi_write_bytes(struct gfx1xm_dev *gfx1xm_dev,
                                u16 addr, u32 data_len, u8 *tx_buf);
int gfx1xm_fw_update(struct gfx1xm_dev* gfx1xm_dev, unsigned char *buf, unsigned short len);
#endif
