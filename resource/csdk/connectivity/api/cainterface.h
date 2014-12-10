/******************************************************************
 *
 * Copyright 2014 Samsung Electronics All Rights Reserved.
 *
 *
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 ******************************************************************/

/**
 * @file cainterface.h
 * @brief This file contains the APIs for Resource Model to use
 */

#ifndef __CA_INTERFACE_H_
#define __CA_INTERFACE_H_

/**
 * Connectivity Abstraction Interface Description APIs.
 */
#include "cacommon.h"

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @brief   Callback function type for request delivery.
 *          requestInfo contains different parameters for resource model to understand about the request.
 * @param   object      [OUT]   Endpoint object from which the request is received. It contains endpoint
 *                              address based on the connectivity type.
 * @param   requestInfo [OUT]   Identifier which needs to be sent with request.
 */
typedef void (*CARequestCallback)(const CARemoteEndpoint_t *object,
                                  const CARequestInfo_t *requestInfo);

/**
 * @brief   Callback function type for response delivery.
 *          responseInfor contains different parameters for resource model to understand about the request.
 * @param   object          [OUT]   Endpoint object from which the response is received.
 * @param   responseInfo    [OUT]   Identifier which needs to be mapped with response.
 */
typedef void (*CAResponseCallback)(const CARemoteEndpoint_t *object,
                                   const CAResponseInfo_t *responseInfo);

/**
 * @brief   Initialize the connectivity abstraction module.
 *          It will initialize adapters, thread pool and other modules based on the platform compilation options.
 *
 * @return  CA_STATUS_OK or ERROR CODES ( CAResult_t error codes in cacommon.h)
 */
CAResult_t CAInitialize();

/**
 * @brief   Terminate the connectivity abstraction module.
 *          All threads, data structures are destroyed for next initializations.
 */
void CATerminate();

/**
 * @brief   Starts listening servers.
 *          This API is used by resource hosting server for listening multicast requests.
 *          based on the adapters configurations , different kinds of servers are started.
 * @return  CA_STATUS_OK or ERROR CODES ( CAResult_t error codes in cacommon.h)
 */
CAResult_t CAStartListeningServer();

/**
 * @brief   Starts discovery servers.
 *          This API is used by resource required clients for listening multicast requests.
 *          based on the adapters configurations , different kinds of servers are started.
 * @return  CA_STATUS_OK or ERROR CODES ( CAResult_t error codes in cacommon.h)
 */
CAResult_t CAStartDiscoveryServer();

/**
 * @brief   Register request callbacks and response callbacks.
 *          requests and responses are delivered these callbacks .
 * @see     CARequestCallback CAResponseCallback
 * @param   ReqHandler   [IN]    Request callback ( for GET,PUT ..etc)
 * @param   RespHandler  [IN]    Response Handler Callback
 * @return  CA_STATUS_OK or ERROR CODES ( CAResult_t error codes in cacommon.h)
 */
CAResult_t CARegisterHandler(CARequestCallback ReqHandler, CAResponseCallback RespHandler);

/**
 * @brief   Create a Remote endpoint if the URI is available already.
 *          for FindResource-> unicast requests , this API is used.
 *          FindResource(URI)-> CACreateRemoteEndpoint , CASendRequest(GET)
 * @param   uri     [IN]    Absolute URI of the resource to be used to generate the Remote endpoint
 *                          for ex : coap://10.11.12.13:4545/resource_uri ( for IP)
 *                          coap://10:11:12:13:45:45/resource_uri ( for BT)
 * @param   object  [OUT ]  Endpoint object which contains the above parsed data
 * @return  CA_STATUS_OK or ERROR CODES ( CAResult_t error codes in cacommon.h)
 */
CAResult_t CACreateRemoteEndpoint(const CAURI_t uri, CARemoteEndpoint_t **object);

/**
 * @brief   API Destroy the remote endpoint created
 * @param   object  [IN]    endpoint object created with CACreateRemoteEndpoint
 */
void CADestroyRemoteEndpoint(CARemoteEndpoint_t *object);

/**
 * @brief   Generating the token for the requests/response.
 *          Token memory is created and destroyed by the calle.
 * @param   token   [OUT]   token for the request
 * @return  CA_STATUS_OK or ERROR CODES ( CAResult_t error codes in cacommon.h)
 */
CAResult_t CAGenerateToken(CAToken_t *token);

/**
 * @brief   Destroy the token generated by CAGenerateToken
 * @param   token   [IN]    token for the request
 */
void CADestroyToken(CAToken_t token);

/**
 * @brief   Find the resource in the network. This API internally sends multicast messages on the
 *          all connectivity adapters. Responses are delivered via response callbacks.
 *
 * @param   resourceUri [IN]    Uri to send multicast search request
 * @return  CA_STATUS_OK or ERROR CODES ( CAResult_t error codes in cacommon.h)
 */
CAResult_t CAFindResource(const CAURI_t resourceUri, const CAToken_t token);

/**
 * @brief   Send control Request on a resource
 * @param   object      [IN]    Remote Endpoint where the payload need to be sent.
 *                              This Remote endpoint is delivered with Request or response callback.
 * @param   requestInfo [IN ]   information for the request.
 * @return  CA_STATUS_OK or ERROR CODES ( CAResult_t error codes in cacommon.h)
 */
CAResult_t CASendRequest(const CARemoteEndpoint_t *object, CARequestInfo_t *requestInfo);

/**
 * @brief   Send control Request on a resource to multicast group
 * @param   object      [IN]    Group Endpoint where the payload need to be sent.
 *                              This Remote endpoint is delivered with Request or response callback.
 * @param   requestInfo [IN ]   information for the request.
 * @return  CA_STATUS_OK or ERROR CODES ( CAResult_t error codes in cacommon.h)
 */
CAResult_t CASendRequestToAll(const CAGroupEndpoint_t* object, 
    const CARequestInfo_t* requestInfo);

/**
 * @brief   Send the response
 * @param   object          [IN]    Remote Endpoint where the payload need to be sent.
 *                                  This Remote endpoint is delivered with Request or response callback
 * @param   responseInfo    [IN ]   information for the response
 * @return  CA_STATUS_OK or ERROR CODES ( CAResult_t error codes in cacommon.h)
 */
CAResult_t CASendResponse(const CARemoteEndpoint_t *object, CAResponseInfo_t *responseInfo);

/**
 * @brief   Send notification to the remote object
 * @param   object          [IN]    Remote Endpoint where the payload need to be sent.
 *                                  This Remote endpoint is delivered with Request or response callback.
 * @param   responseInfo    [IN ]   information for the response.
 * @return  CA_STATUS_OK or ERROR CODES ( CAResult_t error codes in cacommon.h)
 */
CAResult_t CASendNotification(const CARemoteEndpoint_t *object, CAResponseInfo_t *responseInfo);

/**
 * @brief   for advertise the resource
 * @param   resourceUri [IN]    URI to be advertised
 * @param   options     [IN]    header options information
 * @param   numOptions  [IN]    number of options
 * @return  CA_STATUS_OK or ERROR CODES ( CAResult_t error codes in cacommon.h)
 */
CAResult_t CAAdvertiseResource(const CAURI_t resourceUri, CAToken_t token, 
                    CAHeaderOption_t* options,uint8_t numOptions);

/**
 * @brief   Select network to use
 * @param   interestedNetwork   [IN]    Connectivity Type enum
 * @return  CA_STATUS_OK or ERROR CODES ( CAResult_t error codes in cacommon.h)
 */
CAResult_t CASelectNetwork(const uint32_t interestedNetwork);

/**
 * @brief   Select network to unuse
 * @param   nonInterestedNetwork    [IN]    Connectivity Type enum
 * @return  CA_STATUS_OK or ERROR CODES ( CAResult_t error codes in cacommon.h)
 */
CAResult_t CAUnSelectNetwork(const uint32_t nonInterestedNetwork);

/**
 * @brief   Get network information
 *          It should be destroyed by the caller as its Get Information.
 * @param   info    [OUT]   LocalConnectivity objects
 * @param   size    [OUT]   No Of Array objects
 * @return  CA_STATUS_OK or ERROR CODES ( CAResult_t error codes in cacommon.h)
 */
CAResult_t CAGetNetworkInformation(CALocalConnectivity_t **info, uint32_t *size);

/**
 * @brief   for usage of singled threaded application.
 * @return   CA_STATUS_OK or ERROR CODES ( CAResult_t error codes in cacommon.h)
 */
CAResult_t CAHandleRequestResponse();

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
