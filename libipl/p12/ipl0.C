extern "C" {
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <libgen.h>

#include <libpdbg.h>
#include <libpdbg_sbe.h>
}

#include "libipl.H"
#include "libipl_internal.H"
#include <attributes_info.H>
#include<iostream>
#include"iplfacade.H"

#include <filesystem>
#include <fstream>
#include <array>
#include <chrono>
#include <thread>

inline struct pdbg_target* get_pib_target(struct pdbg_target* target)
{
    struct pdbg_target* pib = NULL;

    /* We assume each processor chip contains one and only one pib */
    pdbg_for_each_target("pib", target, pib)
    {
        break;
    }

    if (!pib)
    {
        std::cout << "No pib target associated with target %s"
                  << pdbg_target_path(target) << std::endl;
        return NULL;
    }

    return pib;
}

static void ipl_pre0(void)
{
	ipl_pre();
}

static int ipl_pre_cfam_reset(void)
{
	return -1;
}

static int ipl_cfam_reset(void)
{
	return -1;
}

static int ipl_poweron(void)
{
	return -1;
}

static int ipl_startipl(void)
{
	return -1;
}

static int ipl_disable_attns(void)
{
	return -1;
}

static int ipl_updatehwmodel(void)
{
	return -1;
}

static int ipl_smp_topology(void)
{
	return -1;
}

static int ipl_boot_optimization_check(void)
{
	return -1;
}

static int ipl_set_ref_clock(void)
{
	 struct pdbg_target* hubchip;
	 int ret=-1;
    pdbg_for_each_target("hubchip", NULL, hubchip)
    {
        std::cout << "hubchip found " << std::endl;
        pdbg_target_probe(hubchip);
        if (pdbg_target_status(hubchip) != PDBG_TARGET_ENABLED)
        {
            std::cout << "hubchip chip not enabled " << std::endl;
            return -1;
        }
        pdbg_target* pib = get_pib_target(hubchip);
        pdbg_target_probe(pib);
        if (pdbg_target_status(pib) != PDBG_TARGET_ENABLED)
        {
            std::cout << "pib target for hub chip not enabled " << std::endl;
            return -1;
        }
        std::cout << "invoking ps_set_ref_clock HWP" << std::endl;
        ret = ipl::ps_setup_ref_clock(hubchip);
        if (ret == 0)
        {
            std::cout << "succes in call to HWP ps_set_ref_clock "
                      << std::endl;
        }
		break;
	}
	return ret;
}

static int ipl_clock_test(void)
{
	return -1;
}

static int ipl_hb_config_update(void)
{
	return -1;
}

static int ipl_ph_sppe_config_update(void)
{
	struct pdbg_target* hubchip;
	int ret=-1;
    pdbg_for_each_target("hubchip", NULL, hubchip)
    {
        std::cout << "hubchip found " << std::endl;
        pdbg_target_probe(hubchip);
        if (pdbg_target_status(hubchip) != PDBG_TARGET_ENABLED)
        {
            std::cout << "hubchip chip not enabled " << std::endl;
            return -1;
        }
        pdbg_target* pib = get_pib_target(hubchip);
        pdbg_target_probe(pib);
        if (pdbg_target_status(pib) != PDBG_TARGET_ENABLED)
        {
            std::cout << "pib target for hub chip not enabled " << std::endl;
            return -1;
        }
        std::cout << "invoking ps_sppe_config_update HWP" << std::endl;
        ret = ipl::ps_sppe_config_update(hubchip);
        if (ret == 0)
        {
            std::cout << "succes in call to HWP ps_sppe_config_update "
                      << std::endl;
        }
		break;
    }
	return ret;
}

static int ipl_cbs_start(void)
{
	struct pdbg_target* hubchip;
	int ret=-1;
    pdbg_for_each_target("hubchip", NULL, hubchip)
    {
        std::cout << "hubchip found " << std::endl;
        pdbg_target_probe(hubchip);
        if (pdbg_target_status(hubchip) != PDBG_TARGET_ENABLED)
        {
            std::cout << "hubchip chip not enabled " << std::endl;
            return -1;
        }
        pdbg_target* pib = get_pib_target(hubchip);
        pdbg_target_probe(pib);
        if (pdbg_target_status(pib) != PDBG_TARGET_ENABLED)
        {
            std::cout << "pib target for hub chip not enabled " << std::endl;
            return -1;
        }
        std::cout << "invoking ps_cbs_start HWP" << std::endl;
        ret = ipl::ps_cbs_start(hubchip);
        if (ret == 0)
        {
            std::cout << "succes in call to HWP ps_cbs_start "
                      << std::endl;
        }
        break;
    }
	return ret;
}

static int ipl_startPRD(void)
{
	return -1;
}

static int ipl_proc_attn_listen(void)
{
	return -1;
}

static struct ipl_step ipl0[] = {
	{IPL_DEF(pre_cfam_reset), 0, 1, true, true},
    {IPL_DEF(cfam_reset), 0, 2, true, true},
    {IPL_DEF(poweron), 0, 3, true, true},
    {IPL_DEF(startipl), 0, 4, true, true},
    {IPL_DEF(disable_attns), 0, 5, true, true},
    {IPL_DEF(updatehwmodel), 0, 6, true, true},
    {IPL_DEF(smp_topology), 0, 7, true, true},
    {IPL_DEF(boot_optimization_check), 0, 8, true, true},
    {IPL_DEF(set_ref_clock), 0, 9, true, true},
    {IPL_DEF(clock_test), 0, 10, true, true},
    {IPL_DEF(hb_config_update), 0, 11, true, true},
    {IPL_DEF(ph_sppe_config_update), 0, 12, true, true},
    {IPL_DEF(cbs_start), 0, 13, true, true},
    {IPL_DEF(startPRD), 0, 14, true, true},
    {IPL_DEF(proc_attn_listen), 0, 15, true, true},
    {NULL, NULL, -1, -1, false, false},
};

__attribute__((constructor)) static void ipl_register_ipl0(void)
{
	ipl_register(0, ipl0, ipl_pre0);
}
