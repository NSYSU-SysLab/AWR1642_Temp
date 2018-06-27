/**
 *   @file  mmwave.h
 *
 *   @brief
 *      This is the high level API which is used to abstract the mmWave
 *      link API and allow application developers to be abstracted from
 *      the lower level complexities.
 *
 *  \par
 *  NOTE:
 *      (C) Copyright 2016 Texas Instruments, Inc.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/** @mainpage mmWave API
 *
 *  The mmWave API allow application developers to be abstracted from the lower
 *  layer drivers and the mmWave link API.
 *
 *  The mmWave file should be included in an application as follows:
 *
 *  @code

    #include <ti/control/mmwave/mmwave.h>

    @endcode
 *
 *  ## Initializing the module #
 *
 *  The mmWave module is initialized by using the #MMWave_init API
 *  The module can execute in either of the following domains:
 *  - XWR14xx: The module executes on the MSS
 *  - XWR16xx: The module executes on both the MSS and DSS
 *
 *  ## Synchronizing the module #
 *
 *  Once the module has been initialized it has to be synchronized before it
 *  can be used. This is done using the #MMWave_sync API. This is required
 *  because on the XWR16xx the module can execute on both the DSS and MSS. We
 *  need to ensure that the modules on each domain are operational before
 *  they can be used.
 *
 *  On the XWR14xx; the synchronization is not really required but in order to
 *  maintain the same API behavior between XWR14xx and XWR16xx the API needs to
 *  be invoked.
 *
 *  ## Configuration of the module #
 *
 *  Applications are responsible for populate and configuring the BSS using
 *  the configuration #MMWave_config API. The API will take the application
 *  supplied configuration and will pass this to the BSS via the mmWave link
 *  API(s). Application developers are abstracted from the calling sequence and
 *  the various synchronization events which are required.
 *
 *  Once the configuration has been completed; the application can setup the
 *  data path. After the data path has been successfully configured application
 *  developers can start the mmWave.
 *
 *  ## Starting the mmWave #
 *
 *  After successful configuration the mmWave needs to be started using the
 *  #MMWave_start API. On successful execution of the API the data path
 *  is being excercised.
 *
 *  ## Executing the mmWave module #
 *
 *  The mmWave module requires an execution context which needs to be provided
 *  by the application. This is because there are asynchronous events and
 *  response messages which are received by the BSS using the mmWave Link
 *  infrastructure. Thes need to be handled and processed in the application
 *  supplied execution context.
 *
 *  Failure to provide and execution context and not invoking the
 *  #MMWave_execute API can result in the mmWave API getting stuck
 *  and the application loosing synchronization with the other domains in the
 *  system.
 */

/** @defgroup MMWAVE      mmWave API
 */
#ifndef MMWAVE_H
#define MMWAVE_H

/* mmWave SDK Include Files: */
#include <ti/common/mmwave_error.h>
#include <ti/drivers/crc/crc.h>
#include <ti/drivers/soc/soc.h>
#include <ti/control/mmwavelink/mmwavelink.h>

/**
@defgroup MMWAVE_CTRL_EXTERNAL_FUNCTION            mmWave External Functions
@ingroup MMWAVE
@brief
*   The section has a list of all the exported API which the applications need to
*   invoke in order to use the driver
*/
/**
@defgroup MMWAVE_EXTERNAL_DATA_STRUCTURE      mmWave External Data Structures
@ingroup MMWAVE
@brief
*   The section has a list of all the data structures which are exposed to the
*   application
*/
/**
@defgroup MMWAVE_EXTERNAL_DEFINITIONS      mmWave External Defintions
@ingroup MMWAVE
@brief
*   The section has a list of all external definitions which are exposed by the
*   mmWave module.
*/
/**
@defgroup MMWAVE_ERROR_CODE                   mmWave Error Codes
@ingroup MMWAVE
@brief
*   The section has a list of all the error codes which are generated by the module
*/
/**
@defgroup MMWAVE_INTERNAL_FUNCTION            mmWave Internal Functions
@ingroup MMWAVE
@brief
*   The section has a list of all internal API which are not exposed to the external
*   applications.
*/
/**
@defgroup MMWAVE_INTERNAL_DATA_STRUCTURE      mmWave Internal Data Structures
@ingroup MMWAVE
@brief
*   The section has a list of all internal data structures which are used internally
*   by the mmWave module.
*/
/**
@defgroup MMWAVE_INTERNAL_DEFINITIONS      mmWave Internal Defintions
@ingroup MMWAVE
@brief
*   The section has a list of all internal definitions which are used internally
*   by the mmWave module.
*/

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup MMWAVE_ERROR_CODE
 *  Base error code for the SOC module is defined in the
 *  \include ti/common/mmwave_error.h
 @{ */

/**
 * @brief   Error Code: Invalid argument
 */
#define MMWAVE_EINVAL                   (MMWAVE_ERRNO_BASE-1)

/**
 * @brief   Error Code: mmWave link initialization failed
 */
#define MMWAVE_EINIT                    (MMWAVE_ERRNO_BASE-2)

/**
 * @brief   Error Code: mmWave link not supported
 */
#define MMWAVE_ENOTSUP                  (MMWAVE_ERRNO_BASE-3)

/**
 * @brief   Error Code: mmWave link channel configuration failed
 */
#define MMWAVE_ECHCFG                   (MMWAVE_ERRNO_BASE-4)

/**
 * @brief   Error Code: mmWave link ADC configuration failed
 */
#define MMWAVE_EADCCFG                  (MMWAVE_ERRNO_BASE-5)

/**
 * @brief   Error Code: mmWave link Power configuration failed
 */
#define MMWAVE_EPOWERCFG                (MMWAVE_ERRNO_BASE-6)

/**
 * @brief   Error Code: mmWave link RF initialization failed
 */
#define MMWAVE_ERFINIT                  (MMWAVE_ERRNO_BASE-7)

/**
 * @brief   Error Code: mmWave link profile configuration failed
 */
#define MMWAVE_EPROFILECFG              (MMWAVE_ERRNO_BASE-8)

/**
 * @brief   Error Code: mmWave link chirp configuration failed
 */
#define MMWAVE_ECHIRPCFG                (MMWAVE_ERRNO_BASE-9)

/**
 * @brief   Error Code: mmWave link frame configuration failed
 */
#define MMWAVE_EFRAMECFG                (MMWAVE_ERRNO_BASE-10)

/**
 * @brief   Error Code: mmWave link PLL caliberation failed
 */
#define MMWAVE_EPLLCFG                  (MMWAVE_ERRNO_BASE-11)

/**
 * @brief   Error Code: mmWave link sensor failed
 */
#define MMWAVE_ESENSOR                  (MMWAVE_ERRNO_BASE-12)

/**
 * @brief   Error Code: OS Porting layer services failed
 */
#define MMWAVE_EOS                      (MMWAVE_ERRNO_BASE-13)

/**
 * @brief   Error Code: mmWave Link version error
 */
#define MMWAVE_EVERSION                 (MMWAVE_ERRNO_BASE-14)

/**
 * @brief   Error Code: mmWave message processing error
 */
#define MMWAVE_EMSG                     (MMWAVE_ERRNO_BASE-15)

/**
 * @brief   Error Code: mmWave deinitialization error
 */
#define MMWAVE_EDEINIT                  (MMWAVE_ERRNO_BASE-16)

/**
 * @brief   Error Code: mmWave continuous mode configuration failed
 */
#define MMWAVE_ECONTMODECFG             (MMWAVE_ERRNO_BASE-17)

/**
 * @brief   Error Code: mmWave continuous mode enabling failed
 */
#define MMWAVE_ECONTMODE                (MMWAVE_ERRNO_BASE-18)

/**
 * @brief   Error Code: mmWave link BSS calibration configuration failed
 */
#define MMWAVE_ECALCFG                  (MMWAVE_ERRNO_BASE-19)

/**
 * @brief   Error Code: mmWave link BSS calibration init
 */
#define MMWAVE_ECALINIT                 (MMWAVE_ERRNO_BASE-20)

/**
 * @brief   Error Code: mmWave link BSS calibration periodicity failed
 */
#define MMWAVE_ECALPERIOD               (MMWAVE_ERRNO_BASE-21)

/**
 * @brief   Error Code: mmWave link BSS calibration trigger failed
 */
#define MMWAVE_ECALTRIG                 (MMWAVE_ERRNO_BASE-22)

/**
 * @brief   Error Code: Out of memory error
 */
#define MMWAVE_ENOMEM                   (MMWAVE_ERRNO_BASE-23)

/**
 * @brief   Error Code: Not found
 */
#define MMWAVE_ENOTFOUND                (MMWAVE_ERRNO_BASE-24)

/**
@}
*/

/** @addtogroup MMWAVE_EXTERNAL_DEFINITIONS
 @{ */

/**
 * @brief
 *  mmWave Supported max profiles which can be configured on the BSS
 */
#define   MMWAVE_MAX_PROFILE                4

/**
 * @brief
 *  This is the ACK wait timeout in msec. This is the time for which the
 *  mmWave link module will wait for the reception on an ACK from the BSS. If
 *  this is set to 0 then the mmWave link will not wait for an ACK.
 */
#define   MMWAVE_ACK_TIMEOUT                1000U

/**
@}
*/

/** @addtogroup MMWAVE_EXTERNAL_DATA_STRUCTURE
 @{ */

/**
 * @brief
 *  mmWave Profile Handle
 */
typedef void*   MMWave_ProfileHandle;

/**
 * @brief
 *  mmWave Chirp Handle
 */
typedef void*   MMWave_ChirpHandle;

/**
 * @brief
 *  DFE Data Output Mode
 *
 * @details
 *  The enumeration describes the mode in which the DFE outputs the data
 */
typedef enum MMWave_DFEDataOutputMode_e
{
    /**
     * @brief   The DFE is operating in chirp mode
     */
    MMWave_DFEDataOutputMode_CHIRP      = 0xA0000000,

    /**
     * @brief   The DFE is operating in continuous mode
     */
    MMWave_DFEDataOutputMode_CONTINUOUS
}MMWave_DFEDataOutputMode;

/**
 * @brief
 *  Calibration configuration
 *
 * @details
 *  The structure is used to hold the information which is required
 *  to setup the calibration of the RF.
 */
typedef struct MMWave_CalibrationCfg_t
{
    /**
     * @brief   Flag which determines if calibration is to be enabled or
     * not. 
     */
    bool            enableCalibration;

    /**
     * @brief   Flag which determines if periodic calibration is to be enabled or
     * not. The mmWave will always do one time calibration.
     */
    bool            enablePeriodicity;

    /**
     * @brief   This is valid only if periodicity is enabled and is the time in frames
     * when a calibration report is received by the application through an asynchrous
     * event.
     */
    uint16_t        periodicTimeInFrames;
}MMWave_CalibrationCfg;

/**
 * @brief
 *  ADCBUF configuration
 *
 * @details
 *  The structure is used to hold all the relevant configuration
 *  which is used to configure ADCBUF.
 */
typedef struct MMWave_AdcbufCfg_t
{
    /*! ADCBUF out format:
        0-Complex,
        1-Real */
    uint8_t     adcFmt;

    /*! ADCBUF IQ swap selection:
        0-I in LSB, Q in MSB,
        1-Q in LSB, I in MSB */
    uint8_t     iqSwapSel;

    /*! ADCBUF channel interleave configuration:
        0-interleaved(not supported on XWR16xx),
        1- non-interleaved */
    uint8_t     chInterleave;

    /**
     * @brief   Chirp Threshold configuration used for ADCBUF buffer
     */
    uint8_t     chirpThreshold;
}MMWave_AdcbufCfg;

/**
 * @brief
 *  Chirp mode configuration
 *
 * @details
 *  The structure specifies the configuration which is required to configure
 *  the mmWave link to operate in chirp mode
 */
typedef struct MMWave_DataOutputChirpCfg_t
{
    /**
     * @brief   List of all the active profile handles which can be configured.
     * Setting to NULL indicates that the profile is skipped.
     */
    MMWave_ProfileHandle    profileHandle[MMWAVE_MAX_PROFILE];

    /**
     * @brief   Configuration which is used to setup Frame
     */
    rlFrameCfg_t            frameCfg;
}MMWave_DataOutputChirpCfg;

/**
 * @brief
 *  Continuous mode configuration
 *
 * @details
 *  The structure specifies the configuration which is required to configure
 *  the mmWave link to operate in continuous mode
 */
typedef struct MMWave_DataOutputContinuousCfg_t
{
    /**
     * @brief   Continuous mode configuration
     */
    rlContModeCfg_t         contModeCfg;

    /**
     * @brief   Sample count: This refers to the number of samples per
     * channel.
     */
    uint16_t                dataTransSize;
}MMWave_DataOutputContinuousCfg;

/**
 * @brief
 *  Minimal control configuration
 *
 * @details
 *  The structure specifies the minimal configuration which is required
 *  to setup & initialize the BSS. This is applicable if the configuration
 *  mode is set to MINIMAL.
 */
typedef struct MMWave_MinimalCtrlCfg_t
{
    /**
     * @brief   Configuration which is used to setup Channel
     */
    rlChanCfg_t                 chCfg;

    /**
     * @brief   Low power mode configuration
     */
    rlLowPowerModeCfg_t         lowPowerMode;

    /**
     * @brief   Configuration which is used to setup ADC
     */
    rlAdcOutCfg_t               adcOutCfg;
}MMWave_MinimalCtrlCfg;

/**
 * @brief
 *  Minimal control configuration
 *
 * @details
 *  The structure specifies the full configuration which is required
 *  to setup & initialize the BSS. This is applicable if the configuration
 *  mode is set to FULL.
 */
typedef struct MMWave_FullCtrlCfg_t
{
    /**
     * @brief   Configuration which is used to setup Channel
     */
    rlChanCfg_t                 chCfg;

    /**
     * @brief   Low power mode configuration
     */
    rlLowPowerModeCfg_t         lowPowerMode;

    /**
     * @brief   Configuration which is used to setup ADC
     */
    rlAdcOutCfg_t               adcOutCfg;

    /**
     * @brief   Configuration which is used to setup Device ADCBUF
     */
    MMWave_AdcbufCfg            adcbufCfg;

    /**
     * @brief   DFE Data Output Mode:
     */
    MMWave_DFEDataOutputMode    dfeDataOutputMode;

    union
    {
        /**
         * @brief   Continuous mode configuration:
         */
        MMWave_DataOutputContinuousCfg    continuousModeCfg;

        /**
         * @brief   Chirp mode configuration:
         */
        MMWave_DataOutputChirpCfg         chirpModeCfg;
    }u;
}MMWave_FullCtrlCfg;

/**
 * @brief
 *  Control configuration
 *
 * @details
 *  The structure specifies the configuration which is required to configure
 *  and setup the BSS.
 */
typedef struct MMWave_CtrlCfg_t
{
    /**
     * @brief   Low Frequency Limit for calibrations
     */
    uint16_t        freqLimitLow;

    /**
     * @brief   High Frequency Limit for calibrations
     */
    uint16_t        freqLimitHigh;

    union
    {
        /**
         * @brief   Minimal configuration to be used: This is only applicable
         * if the configuration mode is set to MINIMAL
         */
        MMWave_MinimalCtrlCfg      minimalCfg;

        /**
         * @brief   Full configuration to be used: This is only applicable
         * if the configuration mode is set to FULL
         */
        MMWave_FullCtrlCfg         fullControlCfg;
    }u;
}MMWave_CtrlCfg;

/**
 *  @b Description
 *  @n
 *      Application registered callback function which hooks up with
 *      the mmWave Link events generated by the BSS. Please refer to
 *      the mmWave Link documentation on more information about these
 *      parameters
 *
 *  @param[in]  msgId
 *      Message Identifier
 *  @param[in]  sbId
 *      Subblock identifier
 *  @param[in]  sbLen
 *      Length of the subblock
 *  @param[in]  payload
 *      Pointer to the payload buffer
 *
 *  @retval
 *      Not applicable
 */
typedef void (*MMWave_eventFxn)(uint16_t msgId, uint16_t sbId, uint16_t sbLen, uint8_t *payload);

/**
 *  @b Description
 *  @n
 *      Application registered callback function which is invoked after the configuration
 *      has been used to configure the mmWave link and the BSS. This is applicable only for
 *      the XWR16xx. The BSS can be configured only by the MSS *or* DSS. The callback API is
 *      triggered on the remote execution domain (which did not configure the BSS)
 *
 *  @param[in]  ptrCtrlCfg
 *      Pointer to the control configuration
 *
 *  @retval
 *      Not applicable
 */
typedef void (*MMWave_cfgFxn)(MMWave_CtrlCfg* ptrCtrlCfg);

/**
 *  @b Description
 *  @n
 *      Application registered callback function which is invoked the mmWave link on BSS
 *      has been started. This is applicable only for the XWR16xx. The BSS can be configured
 *      only by the MSS *or* DSS. The callback API is triggered on the remote execution
 *      domain (which did not configure the BSS)
 *
 *  @retval
 *      Not applicable
 */
typedef void (*MMWave_startFxn)(void);

/**
 *  @b Description
 *  @n
 *      Application registered callback function which is invoked the mmWave link on BSS
 *      has been stopped. This is applicable only for the XWR16xx. The BSS can be configured
 *      only by the MSS *or* DSS. The callback API is triggered on the remote execution
 *      domain (which did not configure the BSS)
 *
 *  @retval
 *      Not applicable
 */
typedef void (*MMWave_stopFxn)(void);

/**
 * @brief
 *  mmWave Handle
 */
typedef void*   MMWave_Handle;

/**
 * @brief
 *  Execution Domain
 *
 * @details
 *  Enumeration describes the execution domain for the mmWave
 */
typedef enum MMWave_Domain_e
{
    /**
     * @brief   The mmWave is executing in the MSS domain
     */
    MMWave_Domain_MSS = 0x1,

    /**
     * @brief   The mmWave is executing in the DSS domain
     */
    MMWave_Domain_DSS = 0x2
}MMWave_Domain;

/**
 * @brief
 *  Configuration Mode
 *
 * @details
 *  The mmWave API can be used in either of the following configuration
 *  modes.
 */
typedef enum MMWave_ConfigurationMode_e
{
    /**
     * @brief   Minimal configuration:
     *
     * In this mode the mmWave is responsible for the following:-
     * - Setting up the mmWave Link Transport to the BSS
     * - Start/Stop/Synch capability with the BSS & DSS(if applicable)
     * - Asynch BSS Event notification to the peer domain (if applicable)
     * - mmWave Link initialization
     * - *No* dynamic memory allocation
     *
     * The application is responsible for the following:-
     * - Using the mmWave Link to configure the BSS
     * - Configuration management for the Profile/Chirp and Frame
     * - Sending messages to the peer domain (if applicable)
     *
     * This mode is useful for advanced users.
     */
    MMWave_ConfigurationMode_MINIMAL = 0x1,

    /**
     * @brief   Full configuration:
     *
     * In this mode the mmWave is responsible for the following:-
     * - Setting up the mmWave Link Transport to the BSS
     * - Start/Stop/Synch capability with the BSS & DSS (if applicable)
     * - Asynch BSS Event notification to the peer domain (if applicable)
     * - mmWave Link initialization
     * - Using the mmWave Link to configure the BSS
     * - Configuration management for the Profile/Chirp and Frame
     * - Sending messages to the peer domain (if applicable)
     * - Dynamic memory allocation
     *
     * The application is only responsible for tracking mmWave
     * handles.
     *
     * This mode is useful for basic users.
     */
    MMWave_ConfigurationMode_FULL,
}MMWave_ConfigurationMode;

/**
 * @brief
 *  Execution Mode
 *
 * @details
 *  The enumeration is valid only for the XWR16xx and indicates if the
 *  mmWave module is executing in isolation or cooperative mode.
 */
typedef enum MMWave_ExecutionMode_e
{
    /**
     * @brief   Isolation mode: In this mode the mmWave executes only on
     * the DSS or MSS. There is no exchange of the MMWave configuration or
     * events between the DSS or MSS.
     */
    MMWave_ExecutionMode_ISOLATION = 0,

    /**
     * @brief   Cooperative mode: In this mode the mmWave executes on both
     * the DSS and MSS. MMWave configuration and events are shared between
     * the mmWave execution domains.
     *
     * NOTE: In order for the DSS and MSS realms to communicate with each other
     * the mmWave uses the Mailbox driver with Virtual channel 7. Please ensure
     * that this virtual channel is not used for any other purpose.
     */
    MMWave_ExecutionMode_COOPERATIVE
}MMWave_ExecutionMode;

/**
 * @brief
 *  mmWave Link CRC configuration
 *
 * @details
 *  The structure is used to describe the CRC configuration. The mmWaveLink messages
 *  exchanged between the MSS/DSS and BSS have a checksum applied. The configuration
 *  determines if the checksum computation is to use the CRC Driver *OR* should the
 *  computation be done in the software.
 */
typedef struct MMWave_LinkCRCCfg_t
{
    /**
     * @brief   Flag which if set is used to indicate that the CRC driver is
     * to be used to perform the CRC computation
     */
    uint8_t         useCRCDriver;

    /**
     * @brief   The field is valid only if the CRC Driver is being used else
     * this is ignored.
     */
    CRC_Channel     crcChannel;
}MMWave_LinkCRCCfg;

/**
 * @brief
 *  mmWave Cooperative mode configuration
 *
 * @details
 *  The structure is used to describe configuration supported if the mmWave
 *  is executing in cooperative mode. In this mode each mmWave module domain
 *  is capable of executing the mmWave API and is also responsible for notifying
 *  its peer execution domain on the reception of configuration/events.
 */
typedef struct MMWave_CooperativeModeCfg_t
{
    /**
     * @brief   This is callback function which is invoked on the remote execution
     * domain once the mmWave link has been configured.
     *
     * *NOTE*: This is available only while operating in FULL configuration mode
     * If operating in MINIMAL configuration the application is responsible for
     * the configuration of the BSS using the link API and for passing this
     * information between the peer domains.
     */
    MMWave_cfgFxn       cfgFxn;

    /**
     * @brief   This is callback function which is invoked on the remote execution
     * domain once the mmWave link has been started.
     */
    MMWave_startFxn     startFxn;

    /**
     * @brief   This is callback function which is invoked on the remote execution
     * domain once the mmWave link has been stopped.
     */
    MMWave_stopFxn      stopFxn;
}MMWave_CooperativeModeCfg;

/**
 * @brief
 *  Initial Configuration
 *
 * @details
 *  The structure specifies the configuration which is required to initialize
 *  and setup the mmWave module.
 */
typedef struct MMWave_InitCfg_t
{
    /**
     * @brief   Execution domain on which the mmWave module is executing.
     */
    MMWave_Domain               domain;

    /**
     * @brief   Handle to the SOC Driver
     */
    SOC_Handle                  socHandle;

    /**
     * @brief   Application supplied asynchronous event handler. This is invoked
     * on the reception of an asynchronous event from the BSS
     */
    MMWave_eventFxn             eventFxn;

    /**
     * @brief   mmWave link messages exchanged with the BSS have a checksum. The
     * configuration specifies if the CRC hardware *or* software to be used for
     * checksum calculation and validation.
     */
    MMWave_LinkCRCCfg           linkCRCCfg;

    /**
     * @brief   Configuration Mode:
     */
    MMWave_ConfigurationMode    cfgMode;

#ifdef SOC_XWR16XX
    /**
     * @brief   The execution mode of the mmWave module. On the XWR16xx the mmWave module
     * could execute in either of the following modes:-
     *  (a) [Isolation Mode]: Only on the DSS
     *  (b) [Isolation Mode]: Only on the MSS
     *  (c) [Cooperative Mode]: Control Path on DSS and Data Path on MSS
     *  (d) [Cooperative Mode]: Control Path on MSS and Data Path on DSS
     */
    MMWave_ExecutionMode        executionMode;

    /**
     * @brief   In cooperative mode: The mmWave module is executing on both the DSS
     * and MSS. The module is responsible for passing the configuration and async
     * events between the domains.
     */
    MMWave_CooperativeModeCfg   cooperativeModeCfg;
#endif
}MMWave_InitCfg;

/**
@}
*/

/*******************************************************************************************************
 * mmWave Exported API:
 *******************************************************************************************************/
extern MMWave_Handle MMWave_init (MMWave_InitCfg* ptrCtrlInitCfg, int32_t* errCode);
extern int32_t MMWave_deinit (MMWave_Handle mmWaveHandle, int32_t* errCode);
extern int32_t MMWave_sync (MMWave_Handle mmWaveHandle, int32_t* errCode);
extern int32_t MMWave_config (MMWave_Handle mmWaveHandle, MMWave_CtrlCfg* ptrControlCfg, int32_t* errCode);
extern int32_t MMWave_start (MMWave_Handle mmWaveHandle, MMWave_CalibrationCfg* ptrCalibrationCfg, int32_t* errCode);
extern int32_t MMWave_stop (MMWave_Handle handle, int32_t* errCode);
extern int32_t MMWave_execute (MMWave_Handle mmWaveHandle, int32_t* errCode);

/* Configuration Management API: Available in FULL configuration mode */
extern MMWave_ChirpHandle MMWave_addChirp (MMWave_ProfileHandle profileHandle, rlChirpCfg_t* ptrChirpCfg, int32_t* errCode);
extern int32_t MMWave_delChirp(MMWave_ProfileHandle profileHandle, MMWave_ChirpHandle chirpHandle, int32_t* errCode);
extern int32_t MMWave_getChirpCfg(MMWave_ChirpHandle chirpHandle, rlChirpCfg_t* ptrChirpCfg,int32_t* errCode);
extern MMWave_ProfileHandle MMWave_addProfile (MMWave_Handle mmWaveHandle,rlProfileCfg_t* ptrProfileCfg, int32_t* errCode);
extern int32_t MMWave_getNumProfiles(MMWave_Handle mmWaveHandle, uint32_t* numProfiles, int32_t* errCode);
extern int32_t MMWave_getProfileHandle(MMWave_Handle mmWaveHandle,uint8_t profileIndex,MMWave_ProfileHandle* profileHandle,int32_t* errCode);
extern int32_t MMWave_delProfile (MMWave_Handle mmWaveHandle,MMWave_ProfileHandle profileHandle, int32_t* errCode);
extern int32_t MMWave_getProfileCfg (MMWave_ProfileHandle profileHandle, rlProfileCfg_t* ptrProfileCfg, int32_t* errCode);
extern int32_t MMWave_getNumChirps(MMWave_ProfileHandle profileHandle, uint32_t* numChirps, int32_t* errCode);
extern int32_t MMWave_getChirpHandle(MMWave_ProfileHandle profileHandle, uint32_t chirpIndex, MMWave_ChirpHandle* chirpHandle, int32_t* errCode);
extern int32_t MMWave_flushCfg(MMWave_Handle mmWaveHandle, int32_t* errCode);

#ifdef __cplusplus
}
#endif

#endif /* MMWAVE_H */

