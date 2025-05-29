################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
%.obj: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"/Applications/ti/ccs2002/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla2 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcrc -Ooff --include_path="/Users/charlie/workspace_ccstheia/i2c_ex1_loopback" --include_path="/Users/charlie/ti/C2000Ware_5_04_00_00" --include_path="/Applications/ti/ccs2002/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/include" --define=DEBUG --define=RAM --define=generic_ram_lnk --diag_suppress=10063 --diag_warning=225 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" --include_path="/Users/charlie/workspace_ccstheia/i2c_ex1_loopback/CPU1_RAM/syscfg" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

build-444689119: ../i2c_ex1_loopback.syscfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: SysConfig'
	"/Applications/ti/ccs2002/ccs/utils/sysconfig_1.23.0/sysconfig_cli.sh" --script "/Users/charlie/workspace_ccstheia/i2c_ex1_loopback/i2c_ex1_loopback.syscfg" -o "syscfg" -s "/Users/charlie/ti/C2000Ware_5_04_00_00/.metadata/sdk.json" -b "/boards/LAUNCHXL_F280039C" --context "system" --compiler ccs
	@echo 'Finished building: "$<"'
	@echo ' '

syscfg/board.c: build-444689119 ../i2c_ex1_loopback.syscfg
syscfg/board.h: build-444689119
syscfg/board.cmd.genlibs: build-444689119
syscfg/board.opt: build-444689119
syscfg/board.json: build-444689119
syscfg/pinmux.csv: build-444689119
syscfg/device.c: build-444689119
syscfg/device.h: build-444689119
syscfg/device_cmd.cmd: build-444689119
syscfg/device_cmd.c: build-444689119
syscfg/device_cmd.h: build-444689119
syscfg/device_cmd.opt: build-444689119
syscfg/device_cmd.cmd.genlibs: build-444689119
syscfg/c2000ware_libraries.cmd.genlibs: build-444689119
syscfg/c2000ware_libraries.opt: build-444689119
syscfg/c2000ware_libraries.c: build-444689119
syscfg/c2000ware_libraries.h: build-444689119
syscfg/clocktree.h: build-444689119
syscfg: build-444689119

syscfg/%.obj: ./syscfg/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"/Applications/ti/ccs2002/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla2 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcrc -Ooff --include_path="/Users/charlie/workspace_ccstheia/i2c_ex1_loopback" --include_path="/Users/charlie/ti/C2000Ware_5_04_00_00" --include_path="/Applications/ti/ccs2002/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/include" --define=DEBUG --define=RAM --define=generic_ram_lnk --diag_suppress=10063 --diag_warning=225 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --preproc_with_compile --preproc_dependency="syscfg/$(basename $(<F)).d_raw" --include_path="/Users/charlie/workspace_ccstheia/i2c_ex1_loopback/CPU1_RAM/syscfg" --obj_directory="syscfg" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

f28003x_codestartbranch.obj: /Users/charlie/ti/C2000Ware_5_04_00_00/device_support/f28003x/common/source/f28003x_codestartbranch.asm $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"/Applications/ti/ccs2002/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla2 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcrc -Ooff --include_path="/Users/charlie/workspace_ccstheia/i2c_ex1_loopback" --include_path="/Users/charlie/ti/C2000Ware_5_04_00_00" --include_path="/Applications/ti/ccs2002/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/include" --define=DEBUG --define=RAM --define=generic_ram_lnk --diag_suppress=10063 --diag_warning=225 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" --include_path="/Users/charlie/workspace_ccstheia/i2c_ex1_loopback/CPU1_RAM/syscfg" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


