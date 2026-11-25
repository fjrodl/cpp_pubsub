// Copyright 2026 ulixes
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <chrono>
#include <cmath>
#include <functional>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/int32.hpp"

using namespace std::chrono_literals;

/* Este ejemplo crea una subclase de Node y usa std::bind() para registrar una
 * función miembro como callback de un temporizador. El nodo genera números
 * primos de forma secuencial y los publica en el tópico "primos". */

class PrimosPublisher : public rclcpp::Node
{
public:
  PrimosPublisher()
  : Node("primos_publisher"), current_(1)
  {
    publisher_ = this->create_publisher<std_msgs::msg::Int32>("primos", 10);
    timer_ = this->create_wall_timer(
    1s, std::bind(&PrimosPublisher::timer_callback, this));
    RCLCPP_INFO(this->get_logger(), "Nodo primos_publisher iniciado. Publicando en /primos");
  }

private:
  bool es_primo(int n) const
  {
    if (n < 2) {
      return false;
    }
    if (n == 2) {
      return true;
    }
    if (n % 2 == 0) {
      return false;
    }
    int limite = static_cast<int>(std::sqrt(static_cast<double>(n)));
    for (int i = 3; i <= limite; i += 2) {
      if (n % i == 0) {
        return false;
      }
    }
    return true;
  }

  int siguiente_primo(int n) const
  {
    int candidato = n + 1;
    while (!es_primo(candidato)) {
      ++candidato;
    }
    return candidato;
  }

  void timer_callback()
  {
    current_ = siguiente_primo(current_);
    auto message = std_msgs::msg::Int32();
    message.data = current_;
    RCLCPP_INFO(this->get_logger(), "Publicando primo: %d", message.data);
    publisher_->publish(message);
  }
  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Publisher<std_msgs::msg::Int32>::SharedPtr publisher_;
  int current_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<PrimosPublisher>());
  rclcpp::shutdown();
  return 0;
}
