namespace kg {
	namespace script {
		class ksCode
		{
		protected:
			ksTokenMap m_constructedTokens;
	
			void m_constructTokens( const ksTokenConstructorPriorityMap& tokenConstructors,
									const ksSplitCodeVector& splitCode );
	
		public:
			ksCode( const ksTokenConstructorPriorityMap& tokenConstructors,
					const ksRawTokenMap& rawTokens,
					const std::string& code );
	
			ksCode( const ksTokenConstructorPriorityMap& tokenConstructors,
					const ksSplitCodeVector& splitCode );
	
			static ksSplitCodeVector generateSplitCode( const ksRawTokenMap& rawTokens,
														const std::string& code );
	
			std::shared_ptr<kg::ksClassInstance> execute( ksLibrary& library,
														  std::map<std::string, std::shared_ptr<ksClassInstance>>& stack )const;

			std::shared_ptr<kg::ksClassInstance> execute(ksLibrary& library, std::map<std::string, std::shared_ptr<ksClassInstance>>& stack) const;
		};
	}
}
