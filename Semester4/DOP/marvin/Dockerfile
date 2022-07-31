FROM jenkins/jenkins
ENV JAVA_OPTS -Djenkins.install.runSetupWizard=false
ENV CASC_JENKINS_CONFIG /var/jenkins_home/configuration.yml
ENV CASC_JENKINS_CONFIG /var/jenkins_home/my_marvin.yml
ADD ./job_dsl.groovy /var/jenkins_home
ADD ./my_marvin.yml /var/jenkins_home
ADD ./plugins.txt /usr/share/jenkins/ref/plugins.txt
USER root
RUN apt-get update && apt-get install -y build-essential --fix-missing
RUN /usr/local/bin/install-plugins.sh < /usr/share/jenkins/ref/plugins.txt