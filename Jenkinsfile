pipeline {
    agent any

    environment {
        SONAR_URL = 'http://host.docker.internal:9000'
        SONAR_TOKEN = credentials('sonarqube-token')
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
                            echo "Testing SonarQube connection"
                            curl -I ${SONAR_URL}
                            
                            /opt/sonar-scanner/bin/sonar-scanner --version
                            
                            cat > sonar-project.properties << 'EOF'
sonar.projectKey=Static-3
sonar.projectName=Static-3
sonar.sources=.
sonar.sourceEncoding=UTF-8
sonar.java.binaries=.
EOF
                            
                            echo "Starting scan"
                            
                            /opt/sonar-scanner/bin/sonar-scanner \\
                                -Dsonar.projectKey=Static-3 \\
                                -Dsonar.host.url=${SONAR_URL} \\
                                -Dsonar.login=${TOKEN} \\
                                -Dsonar.sources=.
                        """
                    }
                }
            }
        }

        stage('Wait') {
            steps {
                script {
                    echo "Waiting for analysis"
                    sleep 30
                    
                    sh """
                        echo "Check SonarQube: ${SONAR_URL}/dashboard?id=Static-3"
                        if [ -f ".scannerwork/report-task.txt" ]; then
                            cat .scannerwork/report-task.txt
                        fi
                    """
                }
            }
        }

        stage('Report') {
            steps {
                echo "Scan complete"
                echo "View results at: ${SONAR_URL}"
                sh 'echo "Results in SonarQube" > scan-complete.txt'
            }
        }
    }
}
