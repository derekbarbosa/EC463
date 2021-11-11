################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
fram-utilities/ctpl/peripherals/%.obj: ../fram-utilities/ctpl/peripherals/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"/Applications/ti/ccs1100/ccs/tools/compiler/ti-cgt-msp430_21.6.0.LTS/bin/cl430" -vmspx --code_model=small --data_model=small -O3 --opt_for_speed=0 --use_hw_mpy=F5 --include_path="/Applications/ti/ccs1100/ccs/ccs_base/msp430/include" --include_path="/Users/ryansullivan/Desktop/education/senior/fall/EC463/EC463/src/OutOfBox_MSP430FR2433" --include_path="/Users/ryansullivan/Desktop/education/senior/fall/EC463/EC463/src/OutOfBox_MSP430FR2433/jsmn" --include_path="/Users/ryansullivan/Desktop/education/senior/fall/EC463/EC463/src/OutOfBox_MSP430FR2433/iqmathlib/include" --include_path="/Users/ryansullivan/Desktop/education/senior/fall/EC463/EC463/src/OutOfBox_MSP430FR2433/fram-utilities/ctpl" --include_path="/Users/ryansullivan/Desktop/education/senior/fall/EC463/EC463/src/OutOfBox_MSP430FR2433/fram-utilities/nvs" --include_path="/Users/ryansullivan/Desktop/education/senior/fall/EC463/EC463/src/OutOfBox_MSP430FR2433/driverlib/MSP430FR2xx_4xx" --include_path="/Applications/ti/ccs1100/ccs/tools/compiler/ti-cgt-msp430_21.6.0.LTS/include" --advice:power="all" --advice:hw_config=all --define=__MSP430FR2433__ --define=CTPL_STACK_SIZE=160 -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU40 --preproc_with_compile --preproc_dependency="fram-utilities/ctpl/peripherals/$(basename $(<F)).d_raw" --obj_directory="fram-utilities/ctpl/peripherals" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


