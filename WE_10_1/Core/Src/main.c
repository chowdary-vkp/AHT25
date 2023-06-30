#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stm32f4xx.h>

#define MQTT_HOST "mqtt.myserver.com"
#define MQTT_PORT 1883
#define MQTT_USERNAME "username"
#define MQTT_PASSWORD "password"
#define MQTT_TOPIC "temperature"

int main() {
  char buffer[1024];
  char temperature[10];
  int rc;
  int sockfd;
  struct sockaddr_in6 servaddr;

  // Enable the Ethernet peripheral
  RCC_AHB1ENR |= RCC_AHB1ENR_ETH_EN;

  // Initialize the socket
  sockfd = socket(AF_INET6, SOCK_STREAM, 0);
  if (sockfd < 0) {
    printf("Failed to create a socket: %d\n", sockfd);
    return 1;
  }

  // Initialize the server address
  servaddr.sin6_family = AF_INET6;
  servaddr.sin6_port = htons(MQTT_PORT);
  servaddr.sin6_addr = inet6_addr("::1");

  // Connect to the server
  rc = connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
  if (rc < 0) {
    printf("Failed to connect to the server: %d\n", rc);
    return 1;
  }

  // Read the temperature from the sensor
  sprintf(temperature, "%d", 25);

  // Compose the MQTT message
  sprintf(buffer, "MQTT/%s/%s", MQTT_TOPIC, temperature);

  // Send the MQTT message
  rc = send(sockfd, buffer, strlen(buffer), 0);
  if (rc < 0) {
    printf("Failed to send the MQTT message: %d\n", rc);
    return 1;
  }

  // Close the socket
  close(sockfd);

  return 0;
}
