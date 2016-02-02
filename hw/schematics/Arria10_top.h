#pragma once
#include "mgc_vista_schematics.h"
$includes_begin;
#include <systemc.h>
#include "models_catalogue.h"
#include "Arria_schematics/Arria10_soc.h"
#include "../models/FPGA_AXI_BUS_model.h"
#include "../models/LinuxFrameBufferDisplay_model.h"
#include "../models/ImageCapture_model.h"
#include "../models/fpga_memory_model.h"
#include "../../../A10jpeg/models/JPEG_ENCODER_model.h"
$includes_end;

$module_begin("Arria10_top");
SC_MODULE(Arria10_top) {
public:
  typedef Arria10_top SC_CURRENT_USER_MODULE;
  Arria10_top(::sc_core::sc_module_name name):
    ::sc_core::sc_module(name)
    $initialization_begin
$init("Console1"),
Console1(0)
$end
$init("Console0"),
Console0(0)
$end
$init("fpga_axi_bus"),
fpga_axi_bus(0)
$end
$init("fb"),
fb(0)
$end
$init("ic"),
ic(0)
$end
$init("jpeg"),
jpeg(0)
$end
$init("fpgamem"),
fpgamem(0)
$end
$init("Arria10_soc_inst"),
Arria10_soc_inst(0)
$end
    $initialization_end
{
    $elaboration_begin;
$create_component("Console1");
Console1 = new CONSOLE_pvt("Console1");
$end;
$create_component("Console0");
Console0 = new CONSOLE_pvt("Console0");
$end;
$create_component("fpga_axi_bus");
fpga_axi_bus = new FPGA_AXI_BUS_pvt("fpga_axi_bus");
$end;
$create_component("fb");
fb = new LinuxFrameBufferDisplay_pvt("fb");
$end;
$create_component("ic");
ic = new ImageCapture_pvt("ic");
$end;
$create_component("jpeg");
jpeg = new JPEG_ENCODER_pvt("jpeg");
$end;
$create_component("fpgamem");
fpgamem = new fpga_memory_pvt("fpgamem");
$end;
$create_component("Arria10_soc_inst");
Arria10_soc_inst = new Arria10_soc("Arria10_soc_inst");
$end;
$bind("fpga_axi_bus->JPEGregisters","jpeg->slave");
vista_bind(fpga_axi_bus->JPEGregisters, jpeg->slave);
$end;
$bind("jpeg->master","fpga_axi_bus->JPEGdma");
vista_bind(jpeg->master, fpga_axi_bus->JPEGdma);
$end;
$bind("Arria10_soc_inst->HPS2FPGA_AXI_Master","fpga_axi_bus->FPGAslave");
vista_bind(Arria10_soc_inst->HPS2FPGA_AXI_Master, fpga_axi_bus->FPGAslave);
$end;
$bind("fpga_axi_bus->FPGAmaster","Arria10_soc_inst->FPGA2HPS_AXI_slave");
vista_bind(fpga_axi_bus->FPGAmaster, Arria10_soc_inst->FPGA2HPS_AXI_slave);
$end;
$bind("ic->master","fpga_axi_bus->ICdma");
vista_bind(ic->master, fpga_axi_bus->ICdma);
$end;
$bind("jpeg->irq","Arria10_soc_inst->irq_20");
vista_bind(jpeg->irq, Arria10_soc_inst->irq_20);
$end;
$bind("ic->irq","Arria10_soc_inst->irq_19");
vista_bind(ic->irq, Arria10_soc_inst->irq_19);
$end;
$bind("fpga_axi_bus->ICregisters","ic->slave");
vista_bind(fpga_axi_bus->ICregisters, ic->slave);
$end;
$bind("fpga_axi_bus->FPGAmem","fpgamem->slave");
vista_bind(fpga_axi_bus->FPGAmem, fpgamem->slave);
$end;
$bind("fpga_axi_bus->FrameBuffer","fb->from_bus");
vista_bind(fpga_axi_bus->FrameBuffer, fb->from_bus);
$end;
$bind("Arria10_soc_inst->UART1_TX","Console1->RX");
vista_bind(Arria10_soc_inst->UART1_TX, Console1->RX);
$end;
$bind("Arria10_soc_inst->UART0_TX","Console0->RX");
vista_bind(Arria10_soc_inst->UART0_TX, Console0->RX);
$end;
$bind("Console1->TX","Arria10_soc_inst->UART1_RX");
vista_bind(Console1->TX, Arria10_soc_inst->UART1_RX);
$end;
$bind("Console0->TX","Arria10_soc_inst->UART0_RX");
vista_bind(Console0->TX, Arria10_soc_inst->UART0_RX);
$end;
    $elaboration_end;
  $vlnv_assign_begin;
m_library = "schematics";
m_vendor = "";
m_version = "";
  $vlnv_assign_end;
  }
  ~Arria10_top() {
    $destructor_begin;
$destruct_component("Console1");
delete Console1; Console1 = 0;
$end;
$destruct_component("Console0");
delete Console0; Console0 = 0;
$end;
$destruct_component("fpga_axi_bus");
delete fpga_axi_bus; fpga_axi_bus = 0;
$end;
$destruct_component("fb");
delete fb; fb = 0;
$end;
$destruct_component("ic");
delete ic; ic = 0;
$end;
$destruct_component("jpeg");
delete jpeg; jpeg = 0;
$end;
$destruct_component("fpgamem");
delete fpgamem; fpgamem = 0;
$end;
$destruct_component("Arria10_soc_inst");
delete Arria10_soc_inst; Arria10_soc_inst = 0;
$end;
    $destructor_end;
  }
public:
  $fields_begin;
$component("Console1");
CONSOLE_pvt *Console1;
$end;
$component("Console0");
CONSOLE_pvt *Console0;
$end;
$component("fpga_axi_bus");
FPGA_AXI_BUS_pvt *fpga_axi_bus;
$end;
$component("fb");
LinuxFrameBufferDisplay_pvt *fb;
$end;
$component("ic");
ImageCapture_pvt *ic;
$end;
$component("jpeg");
JPEG_ENCODER_pvt *jpeg;
$end;
$component("fpgamem");
fpga_memory_pvt *fpgamem;
$end;
$component("Arria10_soc_inst");
Arria10_soc *Arria10_soc_inst;
$end;
  $fields_end;
  $vlnv_decl_begin;
public:
const char* m_library;
const char* m_vendor;
const char* m_version;
  $vlnv_decl_end;
};
$module_end;