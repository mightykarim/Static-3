pipeline {
    agent any

    environment {
        SONAR_URL = 'http://localhost:9000'
    }

    stages {
        stage('Checkout') {
            steps {
                checkout([
                    $class: 'GitSCM',
                    branches: [[name: '*/main']],
                    userRemoteConfigs: [[
                        url: 'https://github.com/mightykarim/Static-3.git',
                        credentialsId: 'github-token'
                    ]]
                ])
            }
        }

        stage('SonarQube Scan') {
            steps {
                script {
                    withCredentials([string(credentialsId: 'sonarqube-token', variable: 'TOKEN')]) {
                        sh """
                            echo "Running SonarQube SAST..."
                            /opt/sonar-scanner/bin/sonar-scanner --version
                            
                            /opt/sonar-scanner/bin/sonar-scanner \
                                -Dsonar.projectKey=Static-3 \
                                -Dsonar.host.url=${SONAR_URL} \
                                -Dsonar.login=${TOKEN} \
                                -Dsonar.sources=.
                        """
                    }
                }
            }
        }

        stage('Report') {
            steps {
                echo "✅ SAST Pipeline Complete"
                echo "View results at: ${SONAR_URL}"
                sh 'echo "Lab 12 Complete" > lab-complete.txt'
            }
        }
    }
}
