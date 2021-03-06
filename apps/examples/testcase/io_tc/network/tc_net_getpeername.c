/****************************************************************************
 *
 * Copyright 2016 Samsung Electronics All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
 * either express or implied. See the License for the specific
 * language governing permissions and limitations under the License.
 *
 ****************************************************************************/

// @file tc_net_getpeername.c
// @brief Test Case Example for getpeername() API
#include <tinyara/config.h>
#include <stdio.h>
#include <errno.h>

#include <sys/stat.h>
#include <net/if.h>
#include <arpa/inet.h>
#include <netinet/in.h>
//#include <arch/board/board.h>
#include <apps/netutils/netlib.h>

#include <sys/socket.h>

#include "tc_internal.h"
#include<pthread.h>

#define PORTNUM 1115
#define MAXRCVLEN 20
int sem = 0;
/**
   * @fn                   :getpeername_wait
   * @brief                :function to wait on semaphore
   * @scenario             :
   * API's covered         :
   * Preconditions         :
   * Postconditions        :
   * @return               :void
   */
void getpeername_wait(void)
{
	while (sem <= 0) {

		printf("");
	}
	sem--;
}

/**
   * @fn                   :getpeername_signal
   * @brief                :function to signal semaphore
   * @scenario             :
   * API's covered         :
   * Preconditions         :
   * Postconditions        :
   * @return               :void
   */
void getpeername_signal(void)
{
	sem++;
}

/**
   * @fn                   :tc_net_getpeername_p1
   * @brief                :positive test cases wthout client server model
   * @scenario             :
   * API's covered         :getpeername()
   * Preconditions         :
   * Postconditions        :
   * @return               :void
   */
static void tc_net_getpeername_p1(void)
{
	int sock;
	int len = sizeof(struct sockaddr);
	struct sockaddr foo;

	sock = socket(AF_INET, SOCK_STREAM, 0);
	int ret = getpeername(sock, &foo, (socklen_t *)&len);
	if (ret == -1) {
		printf("tc_net_getpeername_p1: fail\n");

		nw_total_fail++;
		RETURN_ERR;
	}

	printf("tc_net_getpeername_p1: PASS\n");
	nw_total_pass++;
}

/**
   * @fn                   :tc_net_getpeername_sock_n
   * @brief                :negative test case wthout client server model
   * @scenario             :
   * API's covered         :getpeername()
   * Preconditions         :
   * Postconditions        :
   * @return               :void
   */
static void tc_net_getpeername_sock_n(void)
{
	int len = sizeof(struct sockaddr);
	struct sockaddr foo;
	int ret = getpeername(-1, &foo, (socklen_t *)&len);
	if (ret != -1) {
		printf("tc_net_getpeername_sock_n: fail\n");

		nw_total_fail++;
		RETURN_ERR;
	}

	printf("tc_net_getpeername_sock_n: PASS\n");
	nw_total_pass++;
}

/**
   * @fn                   :tc_net_getpeername_close_n
   * @brief                :negative test case wthout client server model
   * @scenario             :
   * API's covered         :getpeername()
   * Preconditions         :
   * Postconditions        :
   * @return               :void
   */
static void tc_net_getpeername_close_n(void)
{
	int sock;
	sock = socket(AF_INET, SOCK_STREAM, 0);
	int len = sizeof(struct sockaddr);
	struct sockaddr foo;
	close(sock);
	int ret = getpeername(sock, &foo, (socklen_t *)&len);
	if (ret != -1) {
		printf("tc_net_getpeername_close_n: fail\n");

		nw_total_fail++;
		RETURN_ERR;
	}

	printf("tc_net_getpeername_close_n: PASS\n");
	nw_total_pass++;
}

/**
   * @fn                   :tc_net_getpeername_unix_p
   * @brief                :
   * @scenario             :
   * API's covered         :getpeername()
   * Preconditions         :
   * Postconditions        :
   * @return               :void
   */
static void tc_net_getpeername_unix_p(void)
{
	int sock;
	int len = sizeof(struct sockaddr);
	struct sockaddr foo;

	sock = socket(AF_UNIX, SOCK_STREAM, 0);
	int ret = getpeername(sock, &foo, (socklen_t *)&len);
	if (ret == -1) {
		printf("tc_net_getpeername_unix_p: fail\n");

		nw_total_fail++;
		RETURN_ERR;
	}
	printf("tc_net_getpeername_unix_p: PASS\n");
	nw_total_pass++;
}

/**
   * @fn                   :tc_net_getpeername_udp_p
   * @brief                :
   * @scenario             :
   * API's covered         :getpeername()
   * Preconditions         :
   * Postconditions        :
   * @return               :void
   */
static void tc_net_getpeername_udp_p(void)
{
	int sock;
	int len = sizeof(struct sockaddr);
	struct sockaddr foo;

	sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	int ret = getpeername(sock, &foo, (socklen_t *)&len);
	if (ret == -1) {
		printf("tc_net_getpeername_udp_p: fail\n");

		nw_total_fail++;
		RETURN_ERR;
	}

	printf("tc_net_getpeername_udp_p: PASS\n");
	nw_total_pass++;
}

/**
   * @fn                   :tc_net_getpeername_p
   * @brief                :positive testcase for  getpeername api with client server model
   * @scenario             :
   * API's covered         :getpeername
   * Preconditions         :
   * Postconditions        :
   * @return               :void
   */
static void tc_net_getpeername_p(int fd)
{
	socklen_t len;
	struct sockaddr_storage addr;
	len = sizeof(addr);

	int ret = getpeername(fd, (struct sockaddr *)&addr, &len);

	if (ret == -1) {
		printf("  \ntc_net_getpeername_p FAIL\n");
		nw_total_fail++;
		RETURN_ERR;
	}
	printf("\ntc_net_getpeername_p:PASS\n");
	nw_total_pass++;

}

/**
   * @fn                   :tc_net_getpeername_n
   * @brief                :negative testcase for  getpeername api with client server model
   * @scenario             :
   * API's covered         :getpeername
   * Preconditions         :
   * Postconditions        :
   * @return               :void
   */
static void tc_net_getpeername_n(int fd)
{
	socklen_t len;
	struct sockaddr_storage addr;
	len = sizeof(addr);

	int ret = getpeername(-1, (struct sockaddr *)&addr, &len);

	if (ret != -1) {
		printf("  \ntc_net_getpeername_n FAIL\n");
		nw_total_fail++;
		RETURN_ERR;
	}
	printf("  \ntc_net_getpeername_n:PASS\n");
	nw_total_pass++;

}

/**
   * @fn                   :getpeername_server
   * @brief                :
   * @scenario             :
   * API's covered         :socket,bind,listen,accept,close
   * Preconditions         :
   * Postconditions        :
   * @return               :void *
   */
void *getpeername_server(void *args)
{

	struct sockaddr_in sa;
	int SocketFD = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	memset(&sa, 0, sizeof(sa));

	sa.sin_family = PF_INET;
	sa.sin_port = htons(PORTNUM);
	sa.sin_addr.s_addr = inet_addr("127.0.0.1");

	bind(SocketFD, (struct sockaddr *)&sa, sizeof(sa));

	listen(SocketFD, 1);
	getpeername_signal();
	int ConnectFD = accept(SocketFD, NULL, NULL);

	close(ConnectFD);

	close(SocketFD);
	return 0;
}

/**
   * @fn                   :getpeername_client
   * @brief                :
   * @scenario             :
   * API's covered         :socket,connect,close
   * Preconditions         :
   * Postconditions        :
   * @return               :void *
   */
void *getpeername_client(void *args)
{

	int mysocket;
	struct sockaddr_in dest;
	mysocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	memset(&dest, 0, sizeof(dest));
	dest.sin_family = PF_INET;
	dest.sin_addr.s_addr = inet_addr("127.0.0.1");
	dest.sin_port = htons(PORTNUM);

	getpeername_wait();
	connect(mysocket, (struct sockaddr *)&dest, sizeof(struct sockaddr));

	tc_net_getpeername_p(mysocket);
	tc_net_getpeername_n(mysocket);

	close(mysocket);
	return 0;

}

/****************************************************************************
 * Name: getpeername()
 ****************************************************************************/
int net_getpeername_main(void)
{

	pthread_t Server, Client;

	pthread_create(&Server, NULL, getpeername_server, NULL);
	pthread_create(&Client, NULL, getpeername_client, NULL);

	pthread_join(Server, NULL);

	pthread_join(Client, NULL);
	tc_net_getpeername_p1();
	tc_net_getpeername_sock_n();
	tc_net_getpeername_close_n();
	tc_net_getpeername_unix_p();
	tc_net_getpeername_udp_p();
	return 0;
}
