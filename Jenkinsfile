pipeline {
    agent any

    environment {
        PROJECT = "Static-3"
        ORG = "mightykarim"
    }

    stages {

        stage('Checkout') {
            steps {
                git branch: 'main', url: 'https://github.com/mightykarim/Static-3.git'
            }
        }

        stage('Build') {
            steps {
                echo "Build step..."
            }
        }
        stage('SonarCloud Analysis') {
            steps {
                withCredentials([string(credentialsId: 'sonarcloud-token', variable: 'TOKEN')]) {
                    withSonarQubeEnv('SonarCloud') {
                        bat """
                            ${tool 'SonarScanner'}\\bin\\sonar-scanner.bat ^
                              -Dsonar.projectKey=Static-3 ^
                              -Dsonar.organization=mightykarim ^
                              -Dsonar.sources=. ^
                              -Dsonar.host.url=https://sonarcloud.io ^
                              -Dsonar.login=%TOKEN% ^
                              -Dsonar.c.file.suffixes=- ^
                              -Dsonar.cpp.file.suffixes=- ^
                              -Dsonar.objc.file.suffixes=-
                        """
                    }
                }
            }
        }


        stage('Quality Gate') {
            steps {
                timeout(time: 2, unit: 'MINUTES') {
                    waitForQualityGate abortPipeline: true
                }
            }
        }

        stage('Deploy') {
            steps {
                echo "Deployment step..."
            }
        }
    }
}
