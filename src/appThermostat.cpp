/**
 *	@file		appThermostat.cpp
 * 	@brief 		appThermostat definition file
 * 	@author		
 * 	@date		
 * 
 */

#include "appThermostat.hpp"
//----------------------------------------------------------------------
void	ThermostatApp::addTemp(float temp){
	
	std::scoped_lock<std::mutex> lock{this->arrayMutex};
	
	uint8_t newPtr = this->getptr();

	if ( newPtr >= (filterSize-1)) newPtr = 0;
	else newPtr++;
	this->setptr(newPtr);

	this->tabTemp.at(newPtr) = temp;

}
//----------------------------------------------------------------------
float	ThermostatApp::getTemp(){
	std::scoped_lock<std::mutex> lock{this->arrayMutex};
	return (std::accumulate(this->tabTemp.begin(),this->tabTemp.end(),0) / filterSize);
}
//----------------------------------------------------------------------
void ThermostatApp::_measureThread(){
	while (true){
		this->addTemp(this->Capteur.getTemp());
		std::this_thread::sleep_for(measure_delay);
	}
	
}
//----------------------------------------------------------------------
void ThermostatApp::_processingThread(){
	float actualTemp;
	while(true){
		std::this_thread::sleep_for(process_delay);
		actualTemp = this->getTemp();
		std::clog << "Actual temperature = " << actualTemp << ". Setpoint is " << this->getConsigne() << std::endl;

		if (actualTemp > (this->getConsigne() + this->getHysteresis()) ){
			try{
				this->pChaudiere->setOFF();
				}
			catch(const std::exception& e){
				std::clog << "Chaudiere already OFF.\n";
			}

		}
		else if (actualTemp < (this->getConsigne() - this->getHysteresis()) ){
			try{
				this->pChaudiere->setON();
				}
			catch(const std::exception& e){
				std::clog << "Chaudiere already ON.\n";
			}
		}
		else{
			std::clog << "No action required...\n";
		}


	}
}
//----------------------------------------------------------------------
void	ThermostatApp::Init(){
	if (this->pChaudiere == nullptr) throw NoBoilerException{};
	this->measureThread = std::jthread(&ThermostatApp::_measureThread, this);
	this->processingThread = std::jthread(&ThermostatApp::_processingThread, this);
}
//----------------------------------------------------------------------
void	ThermostatApp::Run(){
	/**<	 Nothing to do in the main task	*/
}
//----------------------------------------------------------------------
//----------------------------------------------------------------------

