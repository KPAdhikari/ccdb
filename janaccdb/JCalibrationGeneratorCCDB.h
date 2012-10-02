#ifndef JCalibrationGeneratorCCDB_h__
#define JCalibrationGeneratorCCDB_h__

#include <JANA/jerror.h>
#include <JANA/JCalibrationGenerator.h>
#include <string>
#include "JCalibrationCCDB.h"
#include <iostream>
#include "CCDB/CalibrationGenerator.h"

// Place everything in JANA namespace
namespace jana
{

    class JCalibrationGeneratorCCDB: public JCalibrationGenerator
    {
    public:
        
        /** @brief empty ctor       */
        JCalibrationGeneratorCCDB(){
			mGenerator = new ccdb::CalibrationGenerator();
		}

        /** @brief destructor               */
        virtual ~JCalibrationGeneratorCCDB(){}

        /** @brief Get string indicating type of calibration this handles
         *
         * @return string with desctiption
         */
        const char* Description(){return "JCalibration using CCDB";}

        /** @brief    CheckOpenable
         *
         * @parameter [in] url in form "mysql://username@pass:host:port database_name"
         * @parameter [in] run number
         * @parameter [in] name of the variation
         * @return 0.0 - not openable, 0.99 if openable
         */
        double CheckOpenable(std::string url, int run, std::string context)   ///< Test probability of opening the given calibration
        { 
            //std::cout<<"CheckOpenable "<<"url "<<url<<" run "<<run<< " context "<<context<< " url.find(mysql://) "<< url.find("mysql://")<<std::endl;
			if(ccdb::CalibrationGenerator::CheckOpenable(url)) return 0.99;			
            return 0.0;
        } 

        /** @brief MakeJCalibration
         *
         * @parameter [in] url in form "mysql://username@pass:host:port database_name"
         * @parameter [in] run number
         * @parameter [in] name of the variation
         * @return JCalibration pointer or null if error
         */
        JCalibration* MakeJCalibration(std::string url, int run, std::string context) ///< Instantiate an JCalibration object
        {
            return new JCalibrationCCDB(mGenerator->MakeCalibration(url,run,context), url,run,context);
        }
	private:
		//CCDB calibration generator object
		ccdb::CalibrationGenerator *mGenerator;
    };
	

} // Close JANA namespace
#endif // JCalibrationGeneratorCCDB_h__